#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include <QFile>
#include <QMouseEvent>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    QFile styleFile( ":/styles/about.qss" );
    styleFile.open( QFile::ReadOnly );
    setStyleSheet( QString::fromLatin1(styleFile.readAll() ));
    styleFile.close();
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_pushButton_close_clicked()
{
    close();
}
