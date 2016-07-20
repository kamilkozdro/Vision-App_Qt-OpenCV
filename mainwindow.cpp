#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Check filters results tool");

    mainLayout = new QVBoxLayout(this);

    camsFrame = new QFrame();
    optionsFrame = new QFrame();
    optionsFrame->setMaximumWidth(350);

    camsFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    optionsFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);

    camsLayout = new QGridLayout(camsFrame);
    optionsLayout = new QGridLayout(optionsFrame);

    optionsLayout->setSpacing(10);

    labelCamWindow1 = new QLabel();
    labelCamWindow2 = new QLabel();
    labelCamID = new QLabel("Cam ID");
    labelStatus = new QLabel("Status");
    labelFilters = new QLabel("Filters:");
    labelUsedFilters = new QLabel("Used Filters:");

    QList<QLabel*> labels;
    labels << labelCamID << labelStatus << labelFilters << labelUsedFilters;

    foreach(QLabel *label,labels)
    {
        label->setAlignment(Qt::AlignCenter);
        //label->setStyleSheet("background-color: lightgray");
        label->setMaximumHeight(30);
        label->setMaximumWidth(100);
    }

    buttonCam = new QPushButton("Open Cam");
    buttonAddFilter = new QPushButton("Add");
    buttonRemoveFilter = new QPushButton("Remove");

    QList<QPushButton*> buttons;
    buttons << buttonCam << buttonAddFilter << buttonRemoveFilter;

    foreach(QPushButton *button, buttons)
    {
        button->setFixedSize(100,30);
    }

    lineEditCamID = new QLineEdit("0");
    lineEditCamID->setMaximumWidth(20);

    comboBoxFilters = new QComboBox;
    comboBoxWindow1 = new QComboBox;
    comboBoxWindow2 = new QComboBox;

    QList<QComboBox*> comboBoxes;
    comboBoxes << comboBoxFilters << comboBoxWindow1 << comboBoxWindow2;
    foreach(QComboBox *comboBox,comboBoxes)
    {
        comboBox->setMaximumWidth(150);
    }

    comboBoxFilters->addItem("Blur");
    comboBoxFilters->addItem("Gaussian");
    comboBoxFilters->addItem("Laplacian");
    comboBoxFilters->addItem("Sobel");

    comboBoxWindow1->addItem("Unchanged frame");
    comboBoxWindow2->addItem("Unchanged frame");

    listUsedFilters = new QListView;
    usedFilterListModel = new QStringListModel(listUsedFilters);
    listUsedFilters->setMaximumWidth(100);

    mainLayout->addWidget(camsFrame);
    mainLayout->addWidget(optionsFrame);

    camsLayout->addWidget(labelCamWindow1,0,0);
    camsLayout->addWidget(comboBoxWindow1,1,0);
    camsLayout->addWidget(labelCamWindow2,0,1);
    camsLayout->addWidget(comboBoxWindow2,1,1);

    optionsLayout->addWidget(labelCamID,0,0);
    optionsLayout->addWidget(lineEditCamID,0,1);
    optionsLayout->addWidget(buttonCam,1,0);
    optionsLayout->addWidget(labelStatus,1,1);
    optionsLayout->addWidget(labelFilters,2,0);
    optionsLayout->addWidget(comboBoxFilters,2,1);
    optionsLayout->addWidget(buttonAddFilter,3,0);
    optionsLayout->addWidget(buttonRemoveFilter,3,1);
    optionsLayout->addWidget(labelUsedFilters,0,2);
    optionsLayout->addWidget(listUsedFilters,1,2,4,1);

    timer = new QTimer(this);
    timer->start(500);
    connectSignals();
}

MainWindow::~MainWindow()
{

}

QImage MainWindow::Mat2QImage(cv::Mat & src)
{
     cv::Mat temp; // make the same cv::Mat
     cvtColor(src, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
     QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     dest.bits(); // enforce deep copy, see documentation
     // of QImage::QImage ( const uchar * data, int width, int height, Format format )
     return dest;
}

void MainWindow::connectSignals()
{
    connect(timer,&QTimer::timeout,this,&MainWindow::update);
    connect(buttonCam,&QPushButton::released,this,&MainWindow::onReleased_buttonCam);
    connect(buttonAddFilter, &QPushButton::released, this, &MainWindow::onReleased_buttonAddFilter);
    connect(buttonRemoveFilter, &QPushButton::released, this, &MainWindow::onReleased_buttonRemoveFilter);
    connect(comboBoxWindow1, SIGNAL(currentIndexChanged(int)), this, SLOT(onChanged_comboBoxWindow1(int)));
    connect(comboBoxWindow2, SIGNAL(currentIndexChanged(int)), this, SLOT(onChanged_comboBoxWindow2(int)));
}

void MainWindow::update()
{
    if(imgHandler.isCamOpened())
    {
        labelStatus->setText("Opened");
        QImage frame1, frame2;
        cv::Mat cvFrame;
        imgHandler.updateObject();
        imgHandler.getFrame1().copyTo(cvFrame); //kopiowanie obrazu - SLABOOOOO
        frame1 = Mat2QImage(cvFrame);
        imgHandler.getFrame2().copyTo(cvFrame); //kopiowanie obrazu - SLABOOOOO
        frame2 = Mat2QImage(cvFrame);
        labelCamWindow1->setPixmap(QPixmap::fromImage(frame1));
        labelCamWindow2->setPixmap(QPixmap::fromImage(frame2));
    }
    else
    {
        labelStatus->setText("Closed");
    }
}

void MainWindow::addFilterGUI(int index)
{
    QString filterName;
    switch (index)
    {
    case FILTER_BLUR:
        filterName = "Blur";
        break;

    case FILTER_GAUSSIAN:
        filterName = "Gaussian";
        break;

    case FILTER_LAPLACIAN:
        filterName = "Laplacian";
        break;
    case FILTER_SOBEL:
        filterName = "Sobel";
        break;
    default:
        break;
    }
    usedFilterList.append(filterName);
    usedFilterListModel->setStringList(usedFilterList);
    listUsedFilters->setModel(usedFilterListModel);

    comboBoxWindow1->addItem(filterName);
    comboBoxWindow2->addItem(filterName);
}

void MainWindow::removeFilterGUI(int index)
{
    imgHandler.removeFilter(index);
    usedFilterList.removeAt(index);
    usedFilterListModel->setStringList(usedFilterList);
    listUsedFilters->setModel(usedFilterListModel);

    comboBoxWindow1->removeItem(index+1);   // +1, bo zawsze jest Unchanged Frame na index = 0
    comboBoxWindow2->removeItem(index+1);
}

void MainWindow::onReleased_buttonCam()
{
    if(!imgHandler.isCamOpened())
    {
        QString camID = lineEditCamID->text();
        imgHandler.openCam(camID.toInt());
    }
}

void MainWindow::onReleased_buttonAddFilter()
{
    filterWindow = new filterSettingsWindow(comboBoxFilters->currentIndex()+1);

    //connect(filterWindow->getButtonOKPtr(), &QPushButton::released, this, &MainWindow::onReleased_buttonFilterSettingsOK);
    //connect(filterWindow->getButtonCancelPtr(), &QPushButton::released, this, &MainWindow::onReleased_buttonFilterSettingsCancel);
    connect(filterWindow->dialogButtons, SIGNAL(accepted()), this, SLOT(onReleased_buttonFilterSettingsOK()));
    connect(filterWindow->dialogButtons, SIGNAL(rejected()), this, SLOT(onReleased_buttonFilterSettingsCancel()));
    filterWindow->show();
}

void MainWindow::onReleased_buttonRemoveFilter()
{
    QItemSelectionModel *selectedItems = listUsedFilters->selectionModel();
    if(selectedItems->selectedIndexes().size() != 1)
    {
        return; // zwroc blad, zaznaczyc mozna tylko 1 opcje
    }
    else
        removeFilterGUI(listUsedFilters->selectionModel()->currentIndex().row());
}

void MainWindow::onReleased_buttonFilterSettingsOK()
{
    imgHandler.addFilter(filterWindow->getSelectedFilter(), filterWindow->getParameters());
    addFilterGUI(filterWindow->getSelectedFilter());
    filterWindow->hide();
    delete filterWindow;
    filterWindow = NULL;
}

void MainWindow::onReleased_buttonFilterSettingsCancel()
{
    filterWindow->hide();
    delete filterWindow;
    filterWindow = NULL;
}

void MainWindow::onChanged_comboBoxWindow1(int index)
{
    imgHandler.setKeptFrame1(index);
}

void MainWindow::onChanged_comboBoxWindow2(int index)
{
    imgHandler.setKeptFrame2(index);
}
