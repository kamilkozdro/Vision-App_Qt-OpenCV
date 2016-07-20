#ifndef FILTERSETTINGSWINDOW_H
#define FILTERSETTINGSWINDOW_H

#include <QWidget>
#include <QList>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <vector>

//DEFINICJE NOWYCH FILTROW DODAC PONIZEJ
#define FILTER_BLUR 1
#define FILTER_GAUSSIAN 2
#define FILTER_LAPLACIAN 3
#define FILTER_SOBEL 4

class filterSettingsWindow : public QWidget
{
    Q_OBJECT
public:
    //filterSettingsWindow(QWidget *parent = 0);
    filterSettingsWindow(int FILTER_NAME);
    ~filterSettingsWindow();

    std::vector<float> getParameters();
    inline int getSelectedFilter(){return selectedFilter;}
    inline QPushButton* getButtonOKPtr(){return dialogButtons->button(QDialogButtonBox::Ok);}
    inline QPushButton* getButtonCancelPtr(){return dialogButtons->button(QDialogButtonBox::Cancel);}

    QDialogButtonBox *dialogButtons;

private:

    QWidget *parentPtr;
    int selectedFilter;
    //----------*GUI*----------
    QVBoxLayout *mainLayout;
    QFormLayout *formLayout;
    QList<QLineEdit*> editLines;
    QList<QString> labelsNames;

};

#endif // FILTERSETTINGSWINDOW_H
