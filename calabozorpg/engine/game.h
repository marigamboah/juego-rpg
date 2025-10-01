// Dentro de la clase Game (public:)
int getFloor() const;
int getPlayerHP() const;
int getPlayerMaxHP() const;
int getPlayerATK() const;
int getRemainingRolls() const;

std::pair<int,int> rollDice();
TurnResult playerMove(const QString &dir1, const QString &dir2);

Tile getTile(int row, int col) const;

bool save(const std::string &filename);
bool load(const std::string &filename);

void revealAll();
