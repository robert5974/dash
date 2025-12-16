#pragma once

#include "app/pages/page.hpp"

class DashboardPage : public QWidget, public Page {
  Q_OBJECT

public:
  DashboardPage(Arbiter &arbiter);
  void init() override;
};
