#ifndef DISCORDQUOTEFACTORY_H
#define DISCORDQUOTEFACTORY_H

#include <QWidget>
#include <QPushButton>

extern QJsonArray qList;

namespace Ui {
class DiscordQuoteFactory;
}

class DiscordQuoteFactory : public QWidget
{
    Q_OBJECT

public:
    explicit DiscordQuoteFactory(QWidget *parent = nullptr);
    ~DiscordQuoteFactory();
private slots:
    void on_pushButton_about_clicked();
    void on_pushButton_addItem_clicked();
    void on_pushButton_deleteItem_clicked();
    void on_toolButton_filePicker_clicked();
    void on_pushButton_apply_clicked();
    void on_pushButton_selectAll_clicked();
    void on_pushButton_restore_clicked();

private:
    Ui::DiscordQuoteFactory *ui;
    void restore_items(QString path);
};

#endif // DISCORDQUOTEFACTORY_H
