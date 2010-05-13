#ifndef ENGINEER_H
#define ENGINEER_H

#include <QObject>
#include <QDate>

namespace Sem {
  class Device;
  class Tower;

  class Engineer : public QObject {
    Q_OBJECT
  public:
    Engineer(Device*, Tower*);
    void init();

    const QDate& date_hired();
    const QString& name();

    float accuracy();
    float speed();
    float satisfaction();

    int messages_sent();
    int mistakes();

  private:
    Device* d_;
    Tower* tower_;

    QDate date_hired_;
    QString name_;

    int messages_sent_;
    int mistakes_;
  };
}

#endif // ENGINEER_H
