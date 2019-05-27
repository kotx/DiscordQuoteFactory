#include "aboutdialog.h"
#include "discordquotefactory.h"
#include "ui_discordquotefactory.h"

#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMessageBox>
#include <QVariantList>

QJsonArray qList;

DiscordQuoteFactory::DiscordQuoteFactory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiscordQuoteFactory)
{
    ui->setupUi(this);
}

DiscordQuoteFactory::~DiscordQuoteFactory()
{
    delete ui;
}

void DiscordQuoteFactory::restore_items(QString path)
{
    if (!path.isEmpty())
    {
        QFile jsonFile(path);
        if (jsonFile.exists())
        {
            jsonFile.setPermissions(QFile::ReadOther | QFile::WriteOther);

            jsonFile.open(QFile::ReadOnly);
            QJsonDocument qJson = QJsonDocument::fromJson(jsonFile.readAll());
            qList = qJson.array();
            jsonFile.close();

            ui->lineEdit_quotes->setText(path);
            ui->quoteListWidget->clear();
            foreach (QJsonValue q, qList)
            {
                ui->quoteListWidget->addItem(q.toString());
            }
        } else {
            QMessageBox Msgbox;
                Msgbox.setWindowTitle("An error occurred");
                Msgbox.setText("The file you selected does not exist.");
                Msgbox.exec();
        }
    }
}

void DiscordQuoteFactory::on_pushButton_about_clicked()
{
    AboutDialog aboutDialog;

    aboutDialog.setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
    aboutDialog.exec();
}

void DiscordQuoteFactory::on_pushButton_addItem_clicked()
{
    QListWidgetItem *item = new QListWidgetItem("New quote..");
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        ui->quoteListWidget->addItem(item);
}

void DiscordQuoteFactory::on_pushButton_deleteItem_clicked()
{
    qDeleteAll(ui->quoteListWidget->selectedItems());
}

void DiscordQuoteFactory::on_toolButton_filePicker_clicked()
{
    QString quoteFile = QFileDialog::getOpenFileName(this,
                                tr("Select your quotes.json from the Discord folder"), QDir::currentPath());
    ui->lineEdit_quotes->setText(quoteFile);
}

void DiscordQuoteFactory::on_pushButton_apply_clicked()
{
    QList<QString> quotes;
    for(int i = 0; i < ui->quoteListWidget->count(); ++i)
    {
        QListWidgetItem *item = ui->quoteListWidget->item(i);
        quotes.append(item->text());
    }

    QJsonDocument qJson;
    qJson.setArray(QJsonArray::fromStringList(quotes));

    QFile jsonFile(ui->lineEdit_quotes->text());
    if (jsonFile.exists())
    {
        jsonFile.setPermissions(QFile::Permission::ReadOther | QFile::Permission::WriteOther);
        jsonFile.open(QFile::WriteOnly);
        jsonFile.write(qJson.toJson());
        jsonFile.close();

        jsonFile.setPermissions(QFile::Permission::ReadOther);

        QMessageBox Msgbox;
            Msgbox.setWindowTitle("Done!");
            Msgbox.setText("Changes applied.\nYou should restart Discord for the changes to take effect.");
            Msgbox.exec();
    } else {
        QMessageBox Msgbox;
            Msgbox.setWindowTitle("An error occurred");
            Msgbox.setText("The file you selected does not exist.");
            Msgbox.exec();
    }
}

void DiscordQuoteFactory::on_pushButton_selectAll_clicked()
{
    ui->quoteListWidget->selectAll();
}

void DiscordQuoteFactory::on_pushButton_restore_clicked()
{
    restore_items(ui->lineEdit_quotes->text());
}
