#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

#include "app/arbiter.hpp"
#include "app/pages/dashboard.hpp"
#include "app/utilities/icon_engine.hpp"

DashboardPage::DashboardPage(Arbiter &arbiter)
    : Page(arbiter, "Dashboard", "widgets", true, new QWidget()) {
  auto layout = new QHBoxLayout(this->container()->content());
  layout->setContentsMargins(24, 24, 24, 24);
  layout->setSpacing(24);

  auto nav_card = new QPushButton();
  nav_card->setObjectName("DashboardNavCard");
  nav_card->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  // Icon for Navigation Card
  auto nav_layout = new QVBoxLayout(nav_card);
  auto nav_icon = new QLabel();
  nav_icon->setPixmap(QIcon(":/icons/directions_car.svg")
                          .pixmap(64, 64)); // Placeholder size, styling handled
                                            // in QSS if possible or here
  nav_icon->setAlignment(Qt::AlignCenter);
  nav_icon->setAttribute(Qt::WA_TransparentForMouseEvents);
  nav_layout->addStretch();
  nav_layout->addWidget(nav_icon);
  nav_layout->addStretch();

  layout->addWidget(nav_card);

  auto media_card = new QPushButton();
  media_card->setObjectName("DashboardMediaCard");
  media_card->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  // Icon for Media Card
  auto media_layout = new QVBoxLayout(media_card);
  auto media_icon = new QLabel();
  media_icon->setPixmap(
      QIcon(":/icons/play_circle_outline.svg").pixmap(64, 64));
  media_icon->setAlignment(Qt::AlignCenter);
  media_icon->setAttribute(Qt::WA_TransparentForMouseEvents);
  media_layout->addStretch();
  media_layout->addWidget(media_icon);
  media_layout->addStretch();

  layout->addWidget(media_card);

  auto settings_card = new QPushButton();
  settings_card->setObjectName("DashboardSettingsCard");
  settings_card->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  // Icon for Settings Card
  auto settings_layout = new QVBoxLayout(settings_card);
  auto settings_icon = new QLabel();
  settings_icon->setPixmap(
      QIcon(":/icons/tune.svg")
          .pixmap(64, 64)); 
  settings_icon->setAlignment(Qt::AlignCenter);
  settings_icon->setAttribute(Qt::WA_TransparentForMouseEvents);
  settings_layout->addStretch();
  settings_layout->addWidget(settings_icon);
  settings_layout->addStretch();

  layout->addWidget(settings_card);

  // Connections
  // Navigation -> OpenAuto Page
  connect(nav_card, &QPushButton::clicked, [this] {
    this->arbiter.set_curr_page(1); // OpenAuto
  });

  // Multimedia -> Media Page
  connect(media_card, &QPushButton::clicked, [this] {
    this->arbiter.set_curr_page(2); // Media
  });

  // Settings -> Settings Page
  connect(settings_card, &QPushButton::clicked, [this] {
    this->arbiter.set_curr_page(6); // Settings
  });
}

void DashboardPage::init() {}
