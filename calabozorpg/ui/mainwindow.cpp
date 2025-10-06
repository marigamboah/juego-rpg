#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QTableWidgetItem>
#include <QGraphicsDropShadowEffect>
#include <QBrush>
#include <QColor>
#include <QFont>
#include <QHeaderView>
#include <QApplication>
#include <QFontDatabase>
#include <QInputDialog>
#include <QDialog>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QHBoxLayout>

// 🎲 Unicode de dados (⚀⚁⚂⚃⚄⚅)
static QString dieGlyph(int v) {
    if (v >= 1 && v <= 6) return QString(QChar(0x2680 + (v - 1)));
    return QStringLiteral("?");
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // 2) Crear botones Cheat y Tutorial más visibles
    btnCheat    = new QPushButton("CHEAT", this);
    btnTutorial = new QPushButton("TUTORIAL", this);

    // Tamaño y propiedades “llamativas”
    for (QPushButton* b : { btnCheat, btnTutorial }) {
        b->setMinimumSize(140, 42);
        b->setCursor(Qt::PointingHandCursor);
        b->setProperty("variant", "accent");  // se estiliza en styleUI()
    }

    // Intentar colocarlos en tu layout de guardado/carga; si no existe, van a la statusbar
    if (auto hSaveLoad = findChild<QHBoxLayout*>("hSaveLoad")) {
        hSaveLoad->addSpacing(12);
        hSaveLoad->addWidget(btnTutorial);
        hSaveLoad->addWidget(btnCheat);
    } else {
        // fallback visible: status bar (lado derecho)
        ui->statusbar->addPermanentWidget(btnTutorial);
        ui->statusbar->addPermanentWidget(btnCheat);
    }

    // Conexiones
    connect(btnCheat,    &QPushButton::clicked, this, &MainWindow::onCheatButton);
    connect(btnTutorial, &QPushButton::clicked, this, &MainWindow::showTutorialDialog);

    // ===== Tipografías temáticas (videojuego) con fallbacks =====
    // Intento 1: Press Start 2P (arcade), 2: VT323 (retro), 3: Orbitron (sci-fi), fallback: Consolas
    if (QFontDatabase::hasFamily("Press Start 2P")) headingFamily = "Press Start 2P";
    else if (QFontDatabase::hasFamily("Orbitron")) headingFamily = "Orbitron";
    else headingFamily = "Consolas";

    if (QFontDatabase::hasFamily("VT323")) bodyFamily = "VT323";
    else if (QFontDatabase::hasFamily("Press Start 2P")) bodyFamily = "Press Start 2P";
    else bodyFamily = "Consolas";

    // Para emojis nítidos
    if (QFontDatabase::hasFamily("Segoe UI Emoji")) emojiFamily = "Segoe UI Emoji";
    else emojiFamily = font().family();

    qApp->setFont(QFont(bodyFamily, 11));

    setWindowTitle("El Calabozo del Arcángel");
    resize(1000, 600);

    styleUI();
    styleButtons();

    // Tarjetas con sombra suave
    applyCardEffect(ui->table);
    applyCardEffect(ui->logText);

    // HUD (Vidas) + estilo
    setupHUDWidgets();
    styleHUD();

    // Tablero
    setupBoard();
    paintBoard();
    updateHUD();

    // Conexiones básicas
    connect(ui->btnRoll, &QPushButton::clicked, this, &MainWindow::onRollDice);
    connect(ui->btnMove, &QPushButton::clicked, this, &MainWindow::onMove);
    connect(ui->btnSave, &QPushButton::clicked, this, &MainWindow::onSave);
    connect(ui->btnLoad, &QPushButton::clicked, this, &MainWindow::onLoad);
    connect(ui->cheatLine, &QLineEdit::returnPressed, this, &MainWindow::onCheatEntered);

    // Botones permanentes en la barra de estado: Tutorial + Cheat
    btnTutorial = new QPushButton("Tutorial", this);
    btnCheat    = new QPushButton("Cheat", this);
    for (auto *b : {btnTutorial, btnCheat}) {
        b->setCursor(Qt::PointingHandCursor);
        b->setMinimumHeight(26);
        b->setProperty("variant", "ghost"); // usa el estilo “ghost” del stylesheet
        b->style()->unpolish(b); b->style()->polish(b);
    }
    ui->statusbar->addPermanentWidget(btnTutorial);
    ui->statusbar->addPermanentWidget(btnCheat);
    connect(btnTutorial, &QPushButton::clicked, this, &MainWindow::onTutorialButton);
    connect(btnCheat,    &QPushButton::clicked, this, &MainWindow::onCheatButton);

    ui->statusbar->showMessage("Listo para la aventura…");
}
MainWindow::~MainWindow() {
    delete ui;
}

// -------------------- Estilo general --------------------
void MainWindow::styleUI() {
    // Paleta menos chillona (tono bosque/gris frío)
    setStyleSheet(QString(R"(
        QMainWindow {
            background: qlineargradient(x1:0 y1:0, x2:1 y2:1,
                stop:0 #16181d, stop:1 #22262e); /* gris carbón */
            color: #e9ecef;
            font-family: %1;
        }

        QLabel {
            color: #e9ecef;
            font-family: %1;
            font-size: 11pt;
        }

        /* Encabezados HUD */
        #labelFloor, #labelHP, #labelATK, #labelRolls, #labelD1, #labelD2 {
            color: #e1d7bf;              /* beige suave */
            letter-spacing: .6px;
            font-family: %2;
            font-weight: 800;
            font-size: 11.5pt;
        }

        /* Botones base */
        QPushButton {
            background: qlineargradient(x1:0 y1:0, x2:1 y2:1,
                stop:0 #34445a, stop:1 #4b5d78);  /* azul grisáceo */
            color: #f8fafc;
            border: 1px solid #7c8aa1;
            border-radius: 10px;
            padding: 8px 14px;
            font-weight: 700;
            font-family: %2;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0 y1:0, x2:1 y2:1,
                stop:0 #3d516b, stop:1 #5f7594);
            border-color: #aab6c8;
        }
        QPushButton:pressed {
            background: #2b3b50;
            border-color: #cbd5e1;
        }

        /* Variante ghost (para barra de estado) */
        QPushButton[variant="ghost"] {
            background: transparent;
            border: 1px dashed #7c8aa1;
            color: #d7e3f0;
        }
        QPushButton[variant="ghost"]:hover {
            background: rgba(124,138,161,.12);
        }

        /* Tablero: marco y rejilla */
        QTableWidget {
            background-color: #1e2229;  /* gris-azulado oscuro */
            gridline-color:  #3b4656;
            selection-background-color: transparent;
            border: 1px solid #4b5d78;
            border-radius: 10px;
        }
        QHeaderView::section {
            background: transparent;
            border: none;
        }

        QLineEdit, QComboBox {
            background: #1a1f27;
            color: #e9ecef;
            border: 1px solid #3c4a5d;
            border-radius: 8px;
            padding: 6px 8px;
            font-family: %1;
        }
        QTextEdit {
            background: #11151a;
            color: #d2ffe0; /* verde terminal suave */
            border: 1px solid #334457;
            border-radius: 10px;
            font-family: %1;
        }
        QStatusBar { color: #d7e3f0; }
    )").arg(bodyFamily, headingFamily));
}

void MainWindow::styleButtons() {
    ui->btnRoll->setText("Tirar dados");
    ui->btnMove->setText("Mover");
    ui->btnSave->setText("Guardar");
    ui->btnLoad->setText("Cargar");

    // variantes ligeras
    ui->btnRoll->setProperty("variant", "primary");
    ui->btnMove->setProperty("variant", "action");
    ui->btnSave->setProperty("variant", "ghost");
    ui->btnLoad->setProperty("variant", "ghost");

    for (QPushButton *b : {ui->btnRoll, ui->btnMove, ui->btnSave, ui->btnLoad}) {
        if (!b) continue;
        b->style()->unpolish(b);
        b->style()->polish(b);
        auto *sh = new QGraphicsDropShadowEffect(b);
        sh->setBlurRadius(16); sh->setOffset(0, 6); sh->setColor(QColor(0,0,0,140));
        b->setGraphicsEffect(sh);
    }
}

void MainWindow::applyCardEffect(QWidget *w) {
    auto *shadow = new QGraphicsDropShadowEffect(w);
    shadow->setBlurRadius(18);
    shadow->setOffset(0, 6);
    shadow->setColor(QColor(0, 0, 0, 120));
    w->setGraphicsEffect(shadow);
}

// -------------------- HUD --------------------
void MainWindow::setupHUDWidgets() {
    // Cambia etiquetas (sin siglas)
    if (ui->labelHP) ui->labelHP->setText("Vidas");

    // Barra de Vidas
    hpBar = new QProgressBar(this);
    hpBar->setRange(0, 100);
    hpBar->setValue(100);
    hpBar->setTextVisible(true);
    hpBar->setFormat("Vidas %v/%m");
    hpBar->setMinimumWidth(190);

    // Donde estaba el lblHP, mézclalo en tu layout existente:
    // Si tu .ui tiene un grid “gridStats”, úsalo:
    if (auto grid = findChild<QGridLayout*>("gridStats")) {
        if (ui->lblHP) ui->lblHP->setVisible(false);
        grid->addWidget(hpBar, 1, 1);
    } else {
        // fallback: al lado del lblHP si existe
        if (ui->lblHP && ui->lblHP->parentWidget())
            hpBar->setParent(ui->lblHP->parentWidget());
        hpBar->show();
    }

    // Chips
    ui->lblD1->setAlignment(Qt::AlignCenter);
    ui->lblD2->setAlignment(Qt::AlignCenter);
    ui->lblATK->setAlignment(Qt::AlignCenter);
    ui->lblRolls->setAlignment(Qt::AlignCenter);
}

void MainWindow::styleHUD() {
    setStyleSheet(styleSheet() + R"(
        QProgressBar {
            background-color: #161b22;
            border: 1px solid #4b5d78;
            border-radius: 10px;
            text-align: center;
            color: #e9ecef;
            font-weight: 800;
        }
        QProgressBar::chunk {
            background-color: #3fb37f;   /* verde suave */
            border-radius: 10px;
        }
        #lblD1, #lblD2, #lblATK, #lblRolls {
            background: #2a3340;
            color: #e9ecef;
            border: 1px solid #4b5d78;
            border-radius: 10px;
            padding: 3px 10px;
            font-weight: 800;
            min-width: 50px;
            font-family: )" + headingFamily + R"(;
        }
    )");
}

// -------------------- Tablero --------------------
void MainWindow::setupBoard() {
    ui->table->setRowCount(10);
    ui->table->setColumnCount(10);
    ui->table->horizontalHeader()->setVisible(false);
    ui->table->verticalHeader()->setVisible(false);
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table->setSelectionMode(QAbstractItemView::NoSelection);
    ui->table->setWordWrap(false);
    ui->table->setShowGrid(true);
    ui->table->setTextElideMode(Qt::ElideNone);

    const int cell = 48;
    ui->table->horizontalHeader()->setDefaultSectionSize(cell);
    ui->table->verticalHeader()->setDefaultSectionSize(cell);

    QFont emoji(emojiFamily, 18);
    for (int r=0;r<10;++r) {
        for (int c=0;c<10;++c) {
            auto *it = new QTableWidgetItem();
            it->setTextAlignment(Qt::AlignCenter);
            it->setFont(emoji);
            it->setText(QStringLiteral(" "));
            it->setFlags(Qt::ItemIsEnabled);
            ui->table->setItem(r,c,it);
        }
    }
}

QColor MainWindow::colorForTile(TileType t) const {
    // Colores suaves (no chillones) para el fondo de la celda
    switch (t) {
    case TileType::Player: return QColor("#2d3b4e"); // azul grisáceo profundo
    case TileType::Enemy:  return QColor("#4a2f36"); // vino apagado
    case TileType::Chest:  return QColor("#47412a"); // dorado oscuro suave
    case TileType::Tavern: return QColor("#2f4636"); // verde bosque suave
    case TileType::Exit:   return QColor("#403255"); // púrpura grisáceo
    case TileType::Empty:
    default:               return QColor("#1e2229"); // base
    }
}

void MainWindow::paintCell(int r, int c) {
    TileType t = game.getTile(r,c);
    auto *it = ui->table->item(r,c);

    it->setBackground(QBrush(colorForTile(t)));
    it->setFont(QFont(emojiFamily, 18));

    switch (t) {
    case TileType::Empty:  it->setText(QStringLiteral(" ")); break;
    case TileType::Player: it->setText(QStringLiteral("🧝")); break;
    case TileType::Enemy:  it->setText(QStringLiteral("👹")); break;
    case TileType::Chest:  it->setText(QStringLiteral("💰")); break;
    case TileType::Tavern: it->setText(QStringLiteral("🍻")); break;
    case TileType::Exit:   it->setText(QStringLiteral("⛩")); break;
    }
}

void MainWindow::paintBoard() {
    for (int r=0;r<10;++r)
        for (int c=0;c<10;++c)
            paintCell(r,c);
}

// -------------------- HUD --------------------
void MainWindow::updateHUD() {
    ui->lblFloor->setText(QString::number(game.getFloor()));
    ui->lblATK->setText(QString::number(game.getPlayerATK()));
    ui->lblRolls->setText(QString::number(game.getRemainingRolls()));

    // “Vidas”
    if (hpBar) {
        const int hp = game.getPlayerHP();
        const int maxhp = qMax(1, game.getPlayerMaxHP());
        hpBar->setRange(0, maxhp);
        hpBar->setValue(qBound(0, hp, maxhp));
        hpBar->setFormat(QString("Vidas %1/%2").arg(hp).arg(maxhp));

        const double pct = (double)hp / (double)maxhp;
        const QString chunk =
            (pct >= 0.60) ? "#3fb37f" :    // verde
                (pct >= 0.30) ? "#e6b86a" :    // ámbar
                "#d66b6b";     // rojo suave
        hpBar->setStyleSheet(QString(R"(
            QProgressBar {
                background-color: #161b22;
                border: 1px solid #4b5d78;
                border-radius: 10px;
                text-align: center;
                color: #e9ecef;
                font-weight: 800;
            }
            QProgressBar::chunk { background-color: %1; border-radius: 10px; }
        )").arg(chunk));
    }
}

void MainWindow::log(const QString &m) {
    ui->logText->append(m);
}

// -------------------- Flujo de juego --------------------
void MainWindow::handleTurnResult(TurnResult res) {
    switch (res) {
    case TurnResult::Moved:
        log("Te deslizas por los pasillos húmedos del calabozo…");
        break;
    case TurnResult::EnemyDefeated:
        log("La bestia cae. El eco de tu victoria resuena en la piedra.");
        break;
    case TurnResult::PlayerDefeated:
        showDefeatDialog();
        break;
    case TurnResult::ChestOpened:
        log("El cofre cruje y revela su tributo. ¿Acero, vitalidad o bálsamo?");
        break;
    case TurnResult::TavernRest:
        log("Encuentras refugio: una jarra tibia y fuerzas renovadas.");
        break;
    }

    // Si tu engine tiene una forma de saber que ganaste,
    // llama showVictoryDialog() ahí (por ejemplo, al pasar el último piso).
    // showVictoryDialog();
}

// -------------------- Acciones UI --------------------
void MainWindow::onRollDice() {
    auto d  = game.rollDice();
    const int d1 = d.first;
    const int d2 = d.second;
    const int total = d1 + d2;

    ui->lblD1->setText(QString::number(d1));
    ui->lblD2->setText(QString::number(d2));
    updateHUD();

    const QString msg = QString("🎲 Tirada → Dado 1 = %1 %2 | Dado 2 = %3 %4 | Total = %5")
                            .arg(d1).arg(dieGlyph(d1))
                            .arg(d2).arg(dieGlyph(d2))
                            .arg(total);
    log(msg);
    ui->statusbar->showMessage(msg, 3000);

    // 👉 Nuevo mensaje instructivo temático:
    log("Ahora elige las direcciones de movimiento para cada dado.");
    log("Usa los menús desplegables para Dado 1 y Dado 2, luego haz clic en 'Mover'.");
}


void MainWindow::onMove() {
    handleTurnResult(game.playerMove(ui->dir1->currentText(), ui->dir2->currentText()));
    updateHUD();
    paintBoard();
}

void MainWindow::onSave() {
    if (game.save("savegame.json")) log("Grabas tu leyenda en el grimorio. (Partida guardada)");
    else log("Los espíritus se niegan a escribir… (Error al guardar)");
}

void MainWindow::onLoad() {
    if (game.load("savegame.json")) {
        paintBoard(); updateHUD();
        log("El grimorio susurra tu pasado. (Partida cargada)");
    } else {
        log("Las páginas están en blanco… (Error al cargar)");
    }
}

void MainWindow::onCheatEntered() {
    if (ui->cheatLine) ui->cheatLine->clear();
    QMessageBox::information(this, "Cheat", "Usa el botón «Cheat» en la barra inferior.");
}

void MainWindow::onTutorialButton() {
    showTutorialDialog();
}

// -------------------- Cheat (máx. 3 intentos) --------------------
void MainWindow::onCheatButton() {
    if (cheatTries >= kCheatMaxTries) {
        QMessageBox::information(this, "Cheat",
                                 "Has agotado tus intentos. El arcano ya no responde.");
        if (btnCheat) btnCheat->setEnabled(false);
        return;
    }

    const QStringList validAnswers = {
        QStringLiteral("Luis Roberto Villalobos Arias")
};

bool ok = false;
const QString user = QInputDialog::getText(
                         this,
                         "Pregunta de Cheat",
                         "¿Cuál es el nombre completo del profe de algoritmos?",
                         QLineEdit::Normal, "", &ok).trimmed();

if (!ok) { log("El ritual fue interrumpido."); return; }

auto normalize = [](QString s){ return s.simplified().toCaseFolded(); };
bool match = false;
for (const auto &ans : validAnswers) {
    if (normalize(user) == normalize(ans)) { match = true; break; }
}

++cheatTries;

if (match) {
    int hp = game.getPlayerHP();
    int maxhp = game.getPlayerMaxHP();
    int atk = game.getPlayerATK();
    game.setPlayerStats(hp + 1, maxhp + 1, atk); // +1 vida total y cura 1
    updateHUD(); paintBoard();
    log("El pacto se sella: +1 Vida concedida.");
    QMessageBox::information(this, "Cheat",
                             "Respuesta correcta. Los ancestros te otorgan **+1 Vida**.");
    // Puedes desactivar el cheat tras un acierto si quieres:
    // if (btnCheat) btnCheat->setEnabled(false);
} else {
    const int restantes = kCheatMaxTries - cheatTries;
    log("Las runas chisporrotean… esa no es la clave.");
    if (restantes > 0) {
        QMessageBox::warning(this, "Cheat",
                             QString("No es el nombre correcto. Te quedan %1 intento(s).")
                                 .arg(restantes));
    } else {
        QMessageBox::critical(this, "Cheat",
                              "Has agotado los intentos. El conjuro se desvanece.");
        if (btnCheat) btnCheat->setEnabled(false);
    }
}
}

// -------------------- Tutorial / Diálogos --------------------
void MainWindow::showTutorialDialog() {
    QDialog dlg(this);
    dlg.setWindowTitle(QStringLiteral("¿Cómo jugar?"));
    dlg.setModal(true);
    dlg.resize(860, 560);

    // Colores menos chillones, temática fantástica
    dlg.setStyleSheet(QString(R"(
        QDialog {
            background: qlineargradient(x1:0 y1:0, x2:1 y2:1,
                stop:0 #1a1d23, stop:1 #242a33);
            border: 1px solid #4b5d78;
            border-radius: 12px;
            color: #e9ecef;
            font-family: %1;
        }
        QLabel#Title {
            font-family: %2;
            font-size: 20pt;
            font-weight: 900;
            color: #e1d7bf;
            letter-spacing: .8px;
            padding: 6px 0 2px 0;
        }
        QTextBrowser {
            background: #11151a;
            border: 1px solid #3b4656;
            border-radius: 10px;
            padding: 14px 18px;
            color: #dfe7ef;
            font-size: 12.5pt;
            line-height: 1.35em;
            font-family: %1;
        }
        QPushButton {
            background: #3b4656;
            color: #f8fafc;
            border: 1px solid #7c8aa1;
            border-radius: 10px;
            padding: 8px 16px;
            font-weight: 800;
            font-family: %2;
        }
        QPushButton:hover { background: #4b5d78; }
    )").arg(bodyFamily, headingFamily));

    QVBoxLayout v(&dlg);
    QLabel title("¿Cómo jugar?", &dlg);
    title.setObjectName("Title");

    QTextBrowser tb(&dlg);
    tb.setOpenExternalLinks(false);
    tb.setHtml(R"(
        <h3>Tu gesta</h3>
        <p>
          Recorre el calabozo y alcanza la <b>salida</b>. Cada turno lanzas dos dados:
          <b>Dado 1</b> (D1) marca tus primeros pasos; <b>Dado 2</b> (D2), los siguientes.
          Elige la dirección de cada tramo y avanza con astucia.
        </p>

        <h3>El tablero</h3>
        <ul>
          <li><b>Enemigos</b> (👹): mide tu <b>Ataque</b>. Si no basta, sangrarás por el acero.</li>
          <li><b>Cofres</b> (💰): pueden conceder <b>Ataque +1</b>, <b>+1 Vida Máxima</b> o <b>curación</b>.</li>
          <li><b>Tabernas</b> (🍻): un respiro que devuelve parte de tus fuerzas.</li>
          <li><b>Salida</b> (⛩): pisa el umbral y asciende.</li>
        </ul>

        <h3>Poderes y mejoras</h3>
        <ul>
          <li><b>Ataque +1</b>: tu filo golpea más hondo.</li>
          <li><b>+1 Vida Máxima</b>: tu espíritu se ensancha; también sana 1 al instante.</li>
          <li><b>Curación</b>: restaura una porción de tus vidas. Mantén la barra en verde.</li>
        </ul>

        <h3>Consejos del gremio</h3>
        <ul>
          <li>Planifica <i>antes</i> de lanzar. No malgastes pasos.</li>
          <li>Cuida tus <b>Tiradas</b>: cuando se agotan, quedas a merced del laberinto.</li>
          <li>Guarda tu progreso; los héroes prudentes escriben su saga.</li>
        </ul>
    )");

    QHBoxLayout buttons;
    QPushButton close("Cerrar", &dlg);
    buttons.addStretch();
    buttons.addWidget(&close);

    v.addWidget(&title);
    v.addWidget(&tb);
    v.addLayout(&buttons);

    connect(&close, &QPushButton::clicked, &dlg, &QDialog::accept);

    // Centrar en la ventana principal
    const QPoint center = geometry().center() - QPoint(dlg.width()/2, dlg.height()/2);
    dlg.move(center);
    dlg.exec();
}

void MainWindow::showVictoryDialog() {
    QMessageBox box(this);
    box.setWindowTitle("¡Victoria!");
    box.setText("El Arcángel te reconoce: has superado el calabozo.");
    box.setIcon(QMessageBox::Information);
    box.setStyleSheet(R"(
        QMessageBox { background: #1e2229; color: #e9ecef; }
        QLabel { color: #e9ecef; }
        QPushButton {
            background: #3b4656; color: #f8fafc;
            border: 1px solid #7c8aa1; border-radius: 8px; padding: 6px 12px;
            font-weight: 700;
        }
        QPushButton:hover { background: #4b5d78; }
    )");
    box.exec();
}

void MainWindow::showDefeatDialog() {
    QMessageBox box(this);
    box.setWindowTitle("Derrota");
    box.setText("Tu historia no termina aquí. Levántate y vuelve a intentarlo.");
    box.setIcon(QMessageBox::Critical);
    box.setStyleSheet(R"(
        QMessageBox { background: #1e2229; color: #e9ecef; }
        QLabel { color: #e9ecef; }
        QPushButton {
            background: #3b4656; color: #f8fafc;
            border: 1px solid #7c8aa1; border-radius: 8px; padding: 6px 12px;
            font-weight: 700;
        }
        QPushButton:hover { background: #4b5d78; }
    )");
    box.exec();
}

// -------------------- Utilidades --------------------

void MainWindow::setGameControlsEnabled(bool e) {
    QList<QWidget*> widgets = {
        ui->btnRoll,
        ui->btnMove,
        ui->btnSave,
        ui->btnLoad,
        ui->dir1,
        ui->dir2,
        ui->cheatLine,
        ui->table
    };

    for (QWidget* w : widgets) {
        if (w) w->setEnabled(e);
    }

    if (btnCheat)
        btnCheat->setEnabled(e && cheatTries < kCheatMaxTries);
    if (btnTutorial)
        btnTutorial->setEnabled(e);
}


void MainWindow::revealAllTiles() {
    game.revealAll();
    paintBoard();
    log("Mapas antiguos revelan todas las rutas…");
}
