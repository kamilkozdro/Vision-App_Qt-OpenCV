#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "opencv2/opencv.hpp"
#include "imagehandler.h"
#include "filtersettingswindow.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include <QImage>
#include <QPixmap>
#include <QPushButton>
#include <QComboBox>
#include <QListView>
#include <QStringListModel>
#include <QStringList>
#include <QLineEdit>
#include <QTimer>

//DEFINICJE NOWYCH FILTROW DODAC PONIZEJ
#define FILTER_BLUR 1
#define FILTER_GAUSSIAN 2
#define FILTER_LAPLACIAN 3
#define FILTER_SOBEL 4

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addFilterGUI(int index);
    void removeFilterGUI(int index);

private:

    QImage MainWindow::Mat2QImage(cv::Mat & src);
    void connectSignals();

    ImageHandler imgHandler;
    QTimer *timer;
    QStringList usedFilterList;
    QStringListModel *usedFilterListModel;
    //----------*GUI*----------
    QLabel *labelCamWindow1, *labelCamWindow2, *labelCamID, *labelStatus;
    QLabel *labelFilters, *labelUsedFilters;
    QVBoxLayout *mainLayout;
    QGridLayout *camsLayout;
    QGridLayout *optionsLayout;
    QFrame *camsFrame, *optionsFrame;
    QPushButton *buttonCam, *buttonAddFilter, *buttonRemoveFilter;
    QComboBox *comboBoxFilters, *comboBoxWindow1, *comboBoxWindow2;
    QListView *listUsedFilters;
    QLineEdit *lineEditCamID;
    filterSettingsWindow *filterWindow;

private slots:

    void update();
    void onReleased_buttonCam();
    void onReleased_buttonAddFilter();
    void onReleased_buttonRemoveFilter();
    void onReleased_buttonFilterSettingsOK();
    void onReleased_buttonFilterSettingsCancel();
    void onChanged_comboBoxWindow1(int index);
    void onChanged_comboBoxWindow2(int index);
};

#endif // MAINWINDOW_H
