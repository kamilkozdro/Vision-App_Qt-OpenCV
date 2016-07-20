#include "filtersettingswindow.h"

filterSettingsWindow::filterSettingsWindow(int FILTER_NAME)
{
    setWindowTitle("Set Filter Parameters");

    selectedFilter = FILTER_NAME;
    //NOWY FILTR DODAC DO SWITCH/CASE
    switch (selectedFilter)
    {
    case FILTER_BLUR:
        labelsNames << QString("width") << QString("height");
        break;
    case FILTER_GAUSSIAN:
        labelsNames <<  QString("width") <<  QString("height") << QString("sigmaX") <<  QString("sigmaY");
        break;
    case FILTER_LAPLACIAN:
        labelsNames <<  QString("depth") <<  QString("ksize");
        break;
    case FILTER_SOBEL:
        labelsNames <<  QString("depth") <<  QString("dx") <<  QString("dy") <<  QString("ksize");
        break;
    default:
        break;
    }

    mainLayout = new QVBoxLayout(this);
    formLayout = new QFormLayout();
    dialogButtons = new QDialogButtonBox();
    dialogButtons->addButton("OK", QDialogButtonBox::AcceptRole);
    dialogButtons->addButton("Cancel", QDialogButtonBox::RejectRole);

    foreach(QString name,labelsNames)
    {
        auto editLine = new QLineEdit();
        editLines.append(editLine);
        formLayout->addRow(name, editLine);
    }

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(dialogButtons);

}

filterSettingsWindow::~filterSettingsWindow()
{

}

std::vector<float> filterSettingsWindow::getParameters()
{
    std::vector<float> parameters;

    foreach(QLineEdit *editLine, editLines)
    {
        QString param(editLine->text());
        //  DODAJ KONTROLE WPROWADZONYCH DANYCH
        parameters.push_back(param.toFloat());
    }

    return parameters;
}


