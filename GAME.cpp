#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <iostream>

class PieceTextures {
public:
    static sf::Texture blackKing;
    static sf::Texture blackQueen;
    static sf::Texture blackRook;
    static sf::Texture blackKnight;
    static sf::Texture blackBishop;
    static sf::Texture blackPawn;

    static sf::Texture whiteKing;
    static sf::Texture whiteQueen;
    static sf::Texture whiteRook;
    static sf::Texture whiteKnight;
    static sf::Texture whiteBishop;
    static sf::Texture whitePawn;

    static sf::Texture loadTexture(std::string str);
};

class Pieces : public sf::Drawable {

public:

    Pieces(char type = 'P', bool player = true, int pos = -1, bool moved = false)
        : p_name{ type }, p_colour{ player },
        p_positiononboard{ -1 }, p_move{ true }, enpassant{ -1 }
    { }

    void setPiece(char type, bool player, int pos, bool moved = false);

    void setname(char ch) { p_name = ch; setTexture(); }
    char getname() { return p_name; }

    void setcolour(bool bl) { p_colour = bl; setTexture(); }
    bool getcolour() { return p_colour; }

    void setPosition(int pos) { p_positiononboard = pos; move(); }
    int getPosition() { return p_positiononboard; }

    void setMove(bool moved) { p_move = moved; }
    bool getMove() { return p_move; }

    void setenpassant(int x) { enpassant = x; }
    int getenpassant() { return enpassant; }

    std::vector<int>& getPossibleMoves() { return possiblemoves; }
    std::vector<int>& getDangerMoves() { return dangermoves; }

    std::string toString();

private:
    sf::Sprite m_sprite;
    std::vector<int> possiblemoves;
    std::vector<int> dangermoves; // Moves that endanger opposite king

    char p_name; //'K'=King , 'Q' = Queen , 'R' = Rook , 'B' = Bishop , 'N' = Knight , 'P' = Pawn
    bool p_colour; // true == White , false == Black
    int p_positiononboard; // 0-63 board, -1 dead
    int enpassant;
    bool p_move;

    void setTexture();
    void move();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_sprite);
    }
};
sf::Texture PieceTextures::loadTexture(std::string str) {
    sf::Texture tmp;
    if (!tmp.loadFromFile(str))
        std::cout << "Error  loading";
    return tmp;
}

sf::Texture PieceTextures::blackKing = PieceTextures::loadTexture("Textures/b_king.png");
sf::Texture PieceTextures::blackQueen = PieceTextures::loadTexture("Textures/b_queen.png");
sf::Texture PieceTextures::blackRook = PieceTextures::loadTexture("Textures/b_rook.png");
sf::Texture PieceTextures::blackKnight = PieceTextures::loadTexture("Textures/b_knight.png");
sf::Texture PieceTextures::blackBishop = PieceTextures::loadTexture("Textures/b_bishop.png");
sf::Texture PieceTextures::blackPawn = PieceTextures::loadTexture("Textures/b_pawn.png");

sf::Texture PieceTextures::whiteKing = PieceTextures::loadTexture("Textures/w_king.png");
sf::Texture PieceTextures::whiteQueen = PieceTextures::loadTexture("Textures/w_queen.png");
sf::Texture PieceTextures::whiteRook = PieceTextures::loadTexture("Textures/w_rook.png");
sf::Texture PieceTextures::whiteKnight = PieceTextures::loadTexture("Textures/w_knight.png");
sf::Texture PieceTextures::whiteBishop = PieceTextures::loadTexture("Textures/w_bishop.png");
sf::Texture PieceTextures::whitePawn = PieceTextures::loadTexture("Textures/w_pawn.png");

void Pieces::setPiece(char type, bool player, int pos, bool moved) {
    setname(type);
    setcolour(player);
    setPosition(pos); //m_moved true
    setMove(moved); // m_moved false
}

std::string Pieces::toString() {
    std::string str;

    str += p_colour ? "White " : "Black ";

    switch (p_name)
    {
    case 'K':
        str += "King ";
        break;
    case 'Q':
        str += "Queen ";
        break;
    case 'R':
        str += "Rook ";
        break;
    case 'B':
        str += "Bishop ";
        break;
    case 'N':
        str += "Knight ";
        break;
    case 'P':
        str += "Pawn ";
        break;
    default:
        str += "??? ";
        break;
    }

    str += "\nto position\nX: ";
    str += std::to_string((p_positiononboard % 8) + 1);
    str += "  Y: ";
    str += std::to_string((p_positiononboard / 8) + 1);
    str += '\n';


    return str;

}

void Pieces::move() {
    if (p_positiononboard <= -1 || 64 <= p_positiononboard) {
        p_positiononboard = -1;
        m_sprite.setColor(sf::Color(0x00000000));
        m_sprite.setPosition(sf::Vector2f((p_positiononboard % 8) * 64.f + 32.f, (p_positiononboard / 8) * 64.f + 32.f));
        possiblemoves.clear();
        p_move = true;
    }
    else {
        m_sprite.setPosition(sf::Vector2f((p_positiononboard % 8) * 64.f + 32.f, (p_positiononboard / 8) * 64.f + 32.f));
        p_move = true;
    }
    return;
}

void Pieces::setTexture() {
    m_sprite = sf::Sprite();
    switch (p_name)
    {
    case 'K':
        m_sprite.setTexture(p_colour ? PieceTextures::whiteKing : PieceTextures::blackKing);
        break;
    case 'Q':
        m_sprite.setTexture(p_colour ? PieceTextures::whiteQueen : PieceTextures::blackQueen);
        break;
    case 'R':
        m_sprite.setTexture(p_colour ? PieceTextures::whiteRook : PieceTextures::blackRook);
        break;
    case 'B':
        m_sprite.setTexture(p_colour ? PieceTextures::whiteBishop : PieceTextures::blackBishop);
        break;
    case 'N':
        m_sprite.setTexture(p_colour ? PieceTextures::whiteKnight : PieceTextures::blackKnight);
        break;
    case 'P':
        m_sprite.setTexture(p_colour ? PieceTextures::whitePawn : PieceTextures::blackPawn);
        break;
    default:
        std::cerr << "Error piece type does not exist.\n";
        break;
    }
    m_sprite.setOrigin(sf::Vector2f(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2));
    m_sprite.setScale(sf::Vector2f(0.375f, 0.375f));
}

class chessboard : public sf::Drawable {

public:

    chessboard(sf::Color col1 = sf::Color::White, sf::Color col2 = sf::Color::Black);

    // Member function that sets Board stuff, can choose square colors in parameters
    void load(sf::Color col1 = sf::Color::White, sf::Color col2 = sf::Color::Black);

private:

    std::array<sf::RectangleShape, 64> m_boardSquares;

    // Draw class on SFML Window
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
class GameLogic : public sf::Drawable {
private:
    chessboard board;
    std::array<Pieces, 16> whitePieces;
    std::array<Pieces, 16> blackPieces;
    Pieces* selectedPiece;
    std::vector<sf::RectangleShape> possibleMovesSquares;
    std::string lastMove;

    sf::RectangleShape infoRestart;

    sf::Font font;
    sf::Text textRestart;
    sf::Text textTurn;
    sf::Text textSituation;
    sf::Text textLastMove;


    bool selectedpiece;
    bool p_Turn; // true = White turn, false = Black Turn
    bool Checkp_Turn;
    bool mates;
    int turnnum;

    void createMovesSquares();

    void calc_possible_Moves();
    void calc_king_Moves(Pieces* tmpPiece);
    void calc_queen_Moves(Pieces* tmpPiece);
    void calc_rook_Moves(Pieces* tmpPiece);
    void calc_bishop_Moves(Pieces* tmpPiece);
    void calc_knight_Moves(Pieces* tmpPiece);
    void calc_pawn_Moves(Pieces* tmpPiece);
    void calc_Castle_Moves(Pieces* tmpPiece);

    void eraseMoves(Pieces* tmpPiece);

    void checkMate();

    void updateinformation();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    GameLogic(sf::Color bordCol1, sf::Color bordCol2);

    bool getSelected() { return selectedpiece; }

    bool getMate() { return mates; }

    bool selectPiece(int pos);

    void moveSelected(int pos);

    void restartgame();

};

GameLogic::GameLogic(sf::Color bordCol1 = sf::Color::White, sf::Color bordCol2 = sf::Color::Black)
    : board(bordCol1, bordCol2)
{

    font.loadFromFile("Textures/arial.ttf");


    infoRestart.setFillColor(sf::Color::White);
    infoRestart.setOutlineThickness(-5.f);
    infoRestart.setOutlineColor(sf::Color::Black);
    infoRestart.setPosition(sf::Vector2f(512.f, 0.f));
    infoRestart.setSize(sf::Vector2f(256.f, 50.f));

    textRestart.setFont(font);
    textRestart.setString("New Game");
    textRestart.setCharacterSize(23);
    textRestart.setStyle(sf::Text::Bold);
    textRestart.setFillColor(sf::Color::Black);
    textRestart.setPosition(infoRestart.getPosition().x + 75.f, infoRestart.getPosition().y + 10.f);

    textTurn.setFont(font);
    textTurn.setCharacterSize(24);
    textTurn.setStyle(sf::Text::Bold);
    textTurn.setFillColor(sf::Color::White);
    textTurn.setPosition(530.f, 70.f);

    textSituation.setFont(font);
    textSituation.setCharacterSize(24);
    textSituation.setStyle(sf::Text::Bold);
    textSituation.setFillColor(sf::Color::White);
    textSituation.setPosition(530.f, 110.f);

    textLastMove.setFont(font);
    textLastMove.setCharacterSize(24);
    textLastMove.setStyle(sf::Text::Bold);
    textLastMove.setFillColor(sf::Color::White);
    textLastMove.setPosition(530.f, 200.f);


    restartgame();

}


void GameLogic::restartgame() {

    selectedpiece = false;
    p_Turn = true;
    Checkp_Turn = false;
    mates = false;
    turnnum = 1;

    blackPieces[0].setPiece('R', false, 7);
    blackPieces[1].setPiece('N', false, 6);
    blackPieces[2].setPiece('B', false, 5);
    blackPieces[3].setPiece('K', false, 4);
    blackPieces[4].setPiece('Q', false, 3);
    blackPieces[5].setPiece('B', false, 2);
    blackPieces[6].setPiece('N', false, 1);
    blackPieces[7].setPiece('R', false, 0);

    whitePieces[0].setPiece('R', true, 56);
    whitePieces[1].setPiece('N', true, 57);
    whitePieces[2].setPiece('B', true, 58);
    whitePieces[3].setPiece('Q', true, 59);
    whitePieces[4].setPiece('K', true, 60);
    whitePieces[5].setPiece('B', true, 61);
    whitePieces[6].setPiece('N', true, 62);
    whitePieces[7].setPiece('R', true, 63);


    for (int i = 8; i < 16; i++) {
        whitePieces[i].setPiece('P', true, 48 + (i - 8));
        blackPieces[i].setPiece('P', false, 15 - (i - 8));
    }

    calc_possible_Moves();

    textLastMove.setString(" ");


}

void GameLogic::updateinformation() {
    textTurn.setString("Turn: " + std::to_string(turnnum));
    textLastMove.setString(lastMove);

    if (!mates) {
        if (p_Turn)
            textSituation.setString("It's White's Turn");
        else
            textSituation.setString("It's Black's Turn");

        if (Checkp_Turn)
            textSituation.setString(textSituation.getString() + "\nCheck");
    }
    else {
        if (Checkp_Turn) {
            if (p_Turn)
                textSituation.setString("CHECKMATE\nBlack Wins");
            else
                textSituation.setString("CHECKMATE\nWhite Wins");
        }
        else {
            textSituation.setString("STALEMATE\nIts a DRAW");
        }

    }
}

void GameLogic::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.clear(sf::Color::Black);

    target.draw(board);
    target.draw(infoRestart);
    target.draw(textRestart);
    target.draw(textTurn);
    target.draw(textSituation);
    target.draw(textLastMove);

    if ((selectedPiece != NULL) && (selectedpiece)) {
        for (int i = 0; i < possibleMovesSquares.size(); i++) {
            target.draw(possibleMovesSquares.at(i));
        }
    }

    for (int i = 0; i < 16; i++) {
        target.draw(whitePieces[i]);
        target.draw(blackPieces[i]);
    }
}

void GameLogic::createMovesSquares() {

    if (selectedPiece == NULL)
        return;

    possibleMovesSquares.clear();

    for (int i = 0; i < selectedPiece->getPossibleMoves().size(); i++) {
        sf::RectangleShape tmp;
        tmp.setPosition(sf::Vector2f((selectedPiece->getPossibleMoves().at(i) % 8) * 64.f, (selectedPiece->getPossibleMoves().at(i) / 8) * 64.f));
        tmp.setSize(sf::Vector2f(64.f, 64.f));
        tmp.setFillColor(sf::Color(0x66b4cc50));
        possibleMovesSquares.push_back(tmp);
    }

    sf::RectangleShape tmp;
    tmp.setPosition(sf::Vector2f((selectedPiece->getPosition() % 8) * 64.f, (selectedPiece->getPosition() / 8) * 64.f));
    tmp.setSize(sf::Vector2f(64.f, 64.f));
    tmp.setFillColor(sf::Color(0x00000000));
    tmp.setOutlineColor(sf::Color::Red);
    tmp.setOutlineThickness(-3.f);
    possibleMovesSquares.push_back(tmp);

    return;

}



bool GameLogic::selectPiece(int pos) {

    for (int i = 0; i < 16; i++) {
        if (p_Turn) { // If white turn
            if (whitePieces[i].getPosition() == pos) {
                selectedPiece = &whitePieces[i];
                selectedpiece = true;
                break;
            }
        }
        else { // If black turn
            if (blackPieces[i].getPosition() == pos) {
                selectedPiece = &blackPieces[i];
                selectedpiece = true;
                break;
            }
        }
        selectedpiece = false;
    }

    if (!selectedpiece) {
        selectedPiece = NULL;
        possibleMovesSquares.clear();
        return selectedpiece;
    }


    createMovesSquares();

    return selectedpiece;
}



void GameLogic::moveSelected(int pos) {
    bool validMove{ false };

    if ((selectedPiece == NULL) || !selectedpiece) //Probably doesnt need both
        return;

    // Check pos with the Piece's possibleMoves
    for (int i = 0; i < selectedPiece->getPossibleMoves().size(); i++) {
        if (pos == selectedPiece->getPossibleMoves().at(i)) {
            validMove = true;
            break;
        }
    }

    if (validMove) {

        // If Castling Move
        if ((selectedPiece->getname() == 'K') && (!selectedPiece->getMove())) {
            if (selectedPiece->getcolour()) { // If white
                // whitePieces[0] Bot Left Rook, whitePieces[7] Bot Right Rook
                if (pos == 62)
                    whitePieces[7].setPosition(61);
                else if (pos == 58)
                    whitePieces[0].setPosition(59);
            }
            else { // If Black
                // blackPieces[7] Top Left Rook, blackPieces[0] Top Right Rook
                if (pos == 6)
                    blackPieces[0].setPosition(5);
                else if (pos == 2)
                    blackPieces[7].setPosition(3);
            }
        }




        // If Pawn double move (set en passant)
        // White pawn -16, Black pawn +16
        if ((selectedPiece->getname() == 'P')) {
            if (!selectedPiece->getMove()) {
                if (pos == (selectedPiece->getPosition() - 16)) {
                    selectedPiece->setenpassant(selectedPiece->getPosition() - 8);
                }
                else if (pos == (selectedPiece->getPosition() + 16)) {
                    selectedPiece->setenpassant(selectedPiece->getPosition() + 8);
                }
            }
            else {
                for (int i = 0; i < 16; i++) {
                    if (p_Turn) {
                        if (pos == blackPieces[i].getenpassant())
                            blackPieces[i].setPosition(pos);
                    }
                    else {
                        if (pos == whitePieces[i].getenpassant())
                            whitePieces[i].setPosition(pos);
                    }
                }
            }
        }
        if (selectedPiece->getMove()) {
            for (int i = 0; i < 16; i++) {
                whitePieces[i].setenpassant(-1);
                blackPieces[i].setenpassant(-1);
            }
        }


        selectedPiece->setPosition(pos);




        //lastMove = "Last Turn:\n" + selectedPiece->toString();
        for (int i = 0; i < 16; i++) {
            if (selectedPiece->getcolour()) { // If White
                if (blackPieces[i].getPosition() == pos) {
                    blackPieces[i].setPosition(-1);
                    break;
                }
            }
            else { // If Black
                if (whitePieces[i].getPosition() == pos) {
                    whitePieces[i].setPosition(-1);
                    break;
                }
            }
        }



        if (Checkp_Turn) {
            Checkp_Turn = false;
        }

        p_Turn = !p_Turn; // Here player turn changes
        calc_possible_Moves();
    }

    selectedPiece = NULL;
    selectedpiece = false;

}



void GameLogic::calc_possible_Moves() {

    Pieces* tmpPiece;

    // LOOP for every piece
    for (int x = 0; x < 32; x++) {

        if (x < 16)
            tmpPiece = &whitePieces[x];
        else
            tmpPiece = &blackPieces[x - 16];
        tmpPiece->getPossibleMoves().clear();
        tmpPiece->getDangerMoves().clear();

        if (tmpPiece->getPosition() == -1)
            continue;

        // Calculate Moves for tmpPiece by piece type
        switch (tmpPiece->getname())
        {
        case 'K':
            calc_king_Moves(tmpPiece);
            break;
        case 'Q':
            calc_queen_Moves(tmpPiece);
            break;
        case 'R':
            calc_rook_Moves(tmpPiece);
            break;
        case 'B':
            calc_bishop_Moves(tmpPiece);
            break;
        case 'N':
            calc_knight_Moves(tmpPiece);
            break;
        case 'P':
            calc_pawn_Moves(tmpPiece);
            break;
        default:
            std::cerr << "Error piece type does not exist.\n";
            break;
        }
    }


    // Erase illegal moves on current player's pieces
    for (int x = 0; x < 16; x++) {
        if (p_Turn) {
            eraseMoves(&whitePieces[x]);
        }
        else {
            eraseMoves(&blackPieces[x]);
        }
    }



    checkMate();


    updateinformation();
    turnnum++;
}




void GameLogic::eraseMoves(Pieces* tmpPiece) {

    if (tmpPiece->getPosition() == -1)
        return;


    if (tmpPiece->getcolour() == p_Turn) {

        // Erase moves on same team pieces

        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < tmpPiece->getPossibleMoves().size(); j++) {

                if (tmpPiece->getcolour()) { // White
                    if (tmpPiece->getPossibleMoves().at(j) == whitePieces[i].getPosition()) {
                        tmpPiece->getPossibleMoves().erase(tmpPiece->getPossibleMoves().begin() + j);
                        break;
                    }
                }
                else { // Black
                    if (tmpPiece->getPossibleMoves().at(j) == blackPieces[i].getPosition()) {
                        tmpPiece->getPossibleMoves().erase(tmpPiece->getPossibleMoves().begin() + j);
                        break;
                    }
                }
            }
        }

        // Erase King moves on attacked squares
        if (tmpPiece->getname() == 'K') {
            for (int j = 0; j < tmpPiece->getPossibleMoves().size(); j++) {
                for (int i = 0; i < 16; i++) {
                    int o{ 0 };
                    if (tmpPiece->getcolour()) { // White
                        for (o = 0; o < blackPieces[i].getPossibleMoves().size(); o++) {
                            if (tmpPiece->getPossibleMoves().at(j) == blackPieces[i].getPossibleMoves().at(o)) {
                                tmpPiece->getPossibleMoves().erase(tmpPiece->getPossibleMoves().begin() + j--);
                                break;
                            }
                        }
                        if ((o != blackPieces[i].getPossibleMoves().size()))
                            break;;
                    }
                    else { // Black
                        for (o = 0; o < whitePieces[i].getPossibleMoves().size(); o++) {
                            if (tmpPiece->getPossibleMoves().at(j) == whitePieces[i].getPossibleMoves().at(o)) {
                                tmpPiece->getPossibleMoves().erase(tmpPiece->getPossibleMoves().begin() + j--);
                                break;
                            }
                        }
                        if ((o != whitePieces[i].getPossibleMoves().size()))
                            break;;
                    }
                }
            }
        }


        // Erase moves that put current piece's king in check        
        if (tmpPiece->getname() != 'K') {
            for (int i = 0; i < 16; i++) {
                if (p_Turn && (blackPieces[i].getDangerMoves().size() > 1)) {
                    for (int j = 0; j < blackPieces[i].getDangerMoves().size(); j++) {
                        if (blackPieces[i].getDangerMoves().at(j) == tmpPiece->getPosition()) {
                            std::vector<int> tmpMoves;
                            for (int x = 0; x < tmpPiece->getPossibleMoves().size(); x++) {
                                for (int k = 0; k < blackPieces[i].getDangerMoves().size(); k++) {
                                    if (tmpPiece->getPossibleMoves().at(x) == blackPieces[i].getDangerMoves().at(k))
                                        tmpMoves.push_back(tmpPiece->getPossibleMoves().at(x));
                                }
                            }
                            tmpPiece->getPossibleMoves().clear();
                            tmpPiece->getPossibleMoves() = tmpMoves;
                            break;
                        }
                    }
                }
                else if (!p_Turn && (whitePieces[i].getDangerMoves().size() > 1)) {
                    for (int j = 0; j < whitePieces[i].getDangerMoves().size(); j++) {
                        if (whitePieces[i].getDangerMoves().at(j) == tmpPiece->getPosition()) {
                            std::vector<int> tmpMoves;
                            for (int x = 0; x < tmpPiece->getPossibleMoves().size(); x++) {
                                for (int k = 0; k < whitePieces[i].getDangerMoves().size(); k++) {
                                    if (tmpPiece->getPossibleMoves().at(x) == whitePieces[i].getDangerMoves().at(k))
                                        tmpMoves.push_back(tmpPiece->getPossibleMoves().at(x));
                                }
                            }
                            tmpPiece->getPossibleMoves().clear();
                            tmpPiece->getPossibleMoves() = tmpMoves;
                            break;
                        }
                    }
                }
            }
        }


    }
}


void GameLogic::calc_king_Moves(Pieces* tmpPiece) {

    int piecePos{ tmpPiece->getPosition() };
    tmpPiece->getPossibleMoves().clear();

    if ((piecePos / 8) != 0) {
        tmpPiece->getPossibleMoves().push_back(piecePos - 8);
        if ((piecePos % 8) != 0)
            tmpPiece->getPossibleMoves().push_back(piecePos - 9);
        if ((piecePos % 8) != 7)
            tmpPiece->getPossibleMoves().push_back(piecePos - 7);
    }
    if ((piecePos / 8) != 7) {
        tmpPiece->getPossibleMoves().push_back(piecePos + 8);
        if ((piecePos % 8) != 0)
            tmpPiece->getPossibleMoves().push_back(piecePos + 7);
        if ((piecePos % 8) != 7)
            tmpPiece->getPossibleMoves().push_back(piecePos + 9);
    }
    if ((piecePos % 8) != 0)
        tmpPiece->getPossibleMoves().push_back(piecePos - 1);
    if ((piecePos % 8) != 7)
        tmpPiece->getPossibleMoves().push_back(piecePos + 1);


    //calcCastling(tmpPiece);
}


void GameLogic::calc_queen_Moves(Pieces* tmpPiece) {

    int piecePos{ tmpPiece->getPosition() };
    int posCounter{ 1 };

    bool dangerMove{ false };
    bool finishLoop{ false };

    tmpPiece->getPossibleMoves().clear();
    tmpPiece->getDangerMoves().clear();

    // Queen moves left on X axis
    while (((piecePos - posCounter) >= 0) && ((piecePos / 8) == ((piecePos - posCounter) / 8))) {

        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos - posCounter)) || (blackPieces[i].getPosition() == (piecePos - posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos - posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos - posCounter);
            if (!p_Turn) {
                if ((piecePos - posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            }
            else {
                if ((piecePos - posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }

        }

        posCounter += 1;
    }


    // Queen moves right on X axis
    if (!dangerMove) tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 1;
    while ((piecePos / 8) == ((piecePos + posCounter) / 8)) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos + posCounter)) || (blackPieces[i].getPosition() == (piecePos + posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos + posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos + posCounter);
            if (!p_Turn) {
                if ((piecePos + posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            }
            else {
                if ((piecePos + posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }

        }

        posCounter += 1;
    }
    //Queen moves up on Y axis
    if (!dangerMove) tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 8;
    while (((piecePos - posCounter) >= 0) && (posCounter < 64) && ((piecePos % 8) == ((piecePos - posCounter) % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos - posCounter)) || (blackPieces[i].getPosition() == (piecePos - posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos - posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos - posCounter);
            if (!p_Turn) {
                if ((piecePos - posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            }
            else {
                if ((piecePos - posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }

        }

        posCounter += 8;
    }
    //Queen moves down on Y axis
    if (!dangerMove) tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 8;
    while (((piecePos + posCounter) <= 63) && (posCounter < 64) && ((piecePos % 8) == ((piecePos + posCounter) % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos + posCounter)) || (blackPieces[i].getPosition() == (piecePos + posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos + posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos + posCounter);
            if (!p_Turn) {
                if ((piecePos + posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            }
            else {
                if ((piecePos + posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 8;
    }
    // Queen moves towards top left
    if (!dangerMove) tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 9;
    while (((piecePos - posCounter) >= 0) && (((piecePos - posCounter) % 8) < (piecePos % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos - posCounter)) || (blackPieces[i].getPosition() == (piecePos - posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos - posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos - posCounter);
            if (!p_Turn) {
                if ((piecePos - posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            }
            else {
                if ((piecePos - posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 9;
    }
    // Queen moves towards bottom right
    if (!dangerMove) tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 9;
    while (((piecePos + posCounter) <= 63) && (((piecePos + posCounter) % 8) > (piecePos % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos + posCounter)) || (blackPieces[i].getPosition() == (piecePos + posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos + posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos + posCounter);
            if (!p_Turn) {
                if ((piecePos + posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            }
            else {
                if ((piecePos + posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 9;
    }
    // Queen moves towards top right
    if (!dangerMove) tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 7;
    while (((piecePos - posCounter) >= 0) && (((piecePos - posCounter) % 8) > (piecePos % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos - posCounter)) || (blackPieces[i].getPosition() == (piecePos - posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos - posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos - posCounter);
            if (!p_Turn) {
                if ((piecePos - posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            }
            else {
                if ((piecePos - posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 7;
    }
    // Queen moves towards bottom left
    if (!dangerMove) tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 7;
    while (((piecePos + posCounter) <= 63) && (((piecePos + posCounter) % 8) < (piecePos % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos + posCounter)) || (blackPieces[i].getPosition() == (piecePos + posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos + posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos + posCounter);
            if (!p_Turn) {
                if ((piecePos + posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            }
            else {
                if ((piecePos + posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 7;
    }

    if (!dangerMove) tmpPiece->getDangerMoves().clear();


    if (!tmpPiece->getDangerMoves().empty()) {
        int collisions{ 0 };
        for (int j = 0; j < tmpPiece->getDangerMoves().size(); j++) {
            for (int i = 0; i < 16; i++) {
                if (tmpPiece->getDangerMoves().at(j) == blackPieces[i].getPosition()) {
                    collisions++;
                    if (!tmpPiece->getcolour())
                        collisions++;
                }
                if (tmpPiece->getDangerMoves().at(j) == whitePieces[i].getPosition()) {
                    collisions++;
                    if (tmpPiece->getcolour())
                        collisions++;
                }
            }
        }

        if (collisions > 2)
            tmpPiece->getDangerMoves().clear();
    }

    tmpPiece->getDangerMoves().push_back(tmpPiece->getPosition());

}


void GameLogic::calc_rook_Moves(Pieces* tmpPiece) {

    int piecePos = tmpPiece->getPosition();
    int posCounter{ 1 };

    bool dangerMove{ false };
    bool finishLoop{ false };

    tmpPiece->getPossibleMoves().clear();
    tmpPiece->getDangerMoves().clear();

    // Rook moves left on X axis
    while (((piecePos - posCounter) >= 0) && ((piecePos / 8) == ((piecePos - posCounter) / 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos - posCounter)) || (blackPieces[i].getPosition() == (piecePos - posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos - posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos - posCounter);
            if (!p_Turn) {
                if ((piecePos - posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            }
            else {
                if ((piecePos - posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 1;
    }

    // Rook moves right on X axis
    if (!dangerMove) tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 1;
    while ((piecePos / 8) == ((piecePos + posCounter) / 8)) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos + posCounter)) || (blackPieces[i].getPosition() == (piecePos + posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos + posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos + posCounter);
            if (!p_Turn) {
                if ((piecePos + posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            }
            else {
                if ((piecePos + posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 1;
    }

    // Rook moves up on Y axis
    if (!dangerMove) tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 8;
    while (((piecePos - posCounter) >= 0) && (posCounter < 64) && ((piecePos % 8) == ((piecePos - posCounter) % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos - posCounter)) || (blackPieces[i].getPosition() == (piecePos - posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos - posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos - posCounter);
            if (!p_Turn) {
                if ((piecePos - posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            }
            else {
                if ((piecePos - posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 8;
    }

    // Rook moves down on Y axis
    if (!dangerMove) tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 8;
    while (((piecePos + posCounter) <= 63) && (posCounter < 64) && ((piecePos % 8) == ((piecePos + posCounter) % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos + posCounter)) || (blackPieces[i].getPosition() == (piecePos + posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos + posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos + posCounter);
            if (!p_Turn) {
                if ((piecePos + posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            }
            else {
                if ((piecePos + posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 8;
    }

    if (!dangerMove) tmpPiece->getDangerMoves().clear();


    if (!tmpPiece->getDangerMoves().empty()) {
        int collisions{ 0 };
        for (int j = 0; j < tmpPiece->getDangerMoves().size(); j++) {
            for (int i = 0; i < 16; i++) {
                if (tmpPiece->getDangerMoves().at(j) == blackPieces[i].getPosition()) {
                    collisions++;
                    if (!tmpPiece->getcolour())
                        collisions++;
                }
                if (tmpPiece->getDangerMoves().at(j) == whitePieces[i].getPosition()) {
                    collisions++;
                    if (tmpPiece->getcolour())
                        collisions++;
                }
            }
        }

        if (collisions > 2)
            tmpPiece->getDangerMoves().clear();
    }

    tmpPiece->getDangerMoves().push_back(tmpPiece->getPosition());

}


void GameLogic::calc_bishop_Moves(Pieces* tmpPiece) {

    //Normal Bishop Moving
    int piecePos{ tmpPiece->getPosition() };
    int posCounter{ 9 };

    bool dangerMove{ false };
    bool finishLoop{ false };

    tmpPiece->getPossibleMoves().clear();
    tmpPiece->getDangerMoves().clear();

    // Bishop moves towards top left
    while (((piecePos - posCounter) >= 0) && (((piecePos - posCounter) % 8) < (piecePos % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos - posCounter)) || (blackPieces[i].getPosition() == (piecePos - posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos - posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos - posCounter);
            if (!p_Turn) {
                if ((piecePos - posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            }
            else {
                if ((piecePos - posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 9;
    }

    // Bishop moves towards bottom right
    if (!dangerMove) tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 9;
    while (((piecePos + posCounter) <= 63) && (((piecePos + posCounter) % 8) > (piecePos % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos + posCounter)) || (blackPieces[i].getPosition() == (piecePos + posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos + posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos + posCounter);
            if (!p_Turn) {
                if ((piecePos + posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            }
            else {
                if ((piecePos + posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 9;
    }

    // Bishop moves towards top right
    if (!dangerMove) tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 7;
    while (((piecePos - posCounter) >= 0) && (((piecePos - posCounter) % 8) > (piecePos % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos - posCounter)) || (blackPieces[i].getPosition() == (piecePos - posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos - posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos - posCounter);
            if (!p_Turn) {
                if ((piecePos - posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            }
            else {
                if ((piecePos - posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 7;
    }

    // Bishop moves towards bottom left
    if (!dangerMove) tmpPiece->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 7;
    while (((piecePos + posCounter) <= 63) && (((piecePos + posCounter) % 8) < (piecePos % 8))) {
        if (!finishLoop) {
            for (int i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos + posCounter)) || (blackPieces[i].getPosition() == (piecePos + posCounter))) {
                    finishLoop = true;
                    break;
                }
            }
            tmpPiece->getPossibleMoves().push_back(piecePos + posCounter);
        }

        if (!dangerMove) {
            // whitePieces[4] is white King , blackPieces[3] is black King
            tmpPiece->getDangerMoves().push_back(piecePos + posCounter);
            if (!p_Turn) {
                if ((piecePos + posCounter) == blackPieces[3].getPosition())
                    dangerMove = true;
            }
            else {
                if ((piecePos + posCounter) == whitePieces[4].getPosition())
                    dangerMove = true;
            }
        }

        posCounter += 7;
    }

    if (!dangerMove) tmpPiece->getDangerMoves().clear();


    if (!tmpPiece->getDangerMoves().empty()) {
        int collisions{ 0 };
        for (int j = 0; j < tmpPiece->getDangerMoves().size(); j++) {
            for (int i = 0; i < 16; i++) {
                if (tmpPiece->getDangerMoves().at(j) == blackPieces[i].getPosition()) {
                    collisions++;
                    if (!tmpPiece->getcolour())
                        collisions++;
                }
                if (tmpPiece->getDangerMoves().at(j) == whitePieces[i].getPosition()) {
                    collisions++;
                    if (tmpPiece->getcolour())
                        collisions++;
                }
            }
        }

        if (collisions > 2)
            tmpPiece->getDangerMoves().clear();
    }

    tmpPiece->getDangerMoves().push_back(tmpPiece->getPosition());


}


void GameLogic::calc_knight_Moves(Pieces* tmpPiece) {

    tmpPiece->getPossibleMoves().clear();

    int piecePos{ tmpPiece->getPosition() };

    if ((piecePos / 8) != 0) {
        if ((piecePos % 8) >= 2)
            tmpPiece->getPossibleMoves().push_back(piecePos - 10);
        if ((piecePos % 8) <= 5)
            tmpPiece->getPossibleMoves().push_back(piecePos - 6);
        if ((piecePos / 8) != 1) {
            if ((piecePos % 8) >= 1)
                tmpPiece->getPossibleMoves().push_back(piecePos - 17);
            if ((piecePos % 8) <= 6)
                tmpPiece->getPossibleMoves().push_back(piecePos - 15);
        }
    }
    if ((piecePos / 8) != 7) {
        if ((piecePos % 8) >= 2)
            tmpPiece->getPossibleMoves().push_back(piecePos + 6);
        if ((piecePos % 8) <= 5)
            tmpPiece->getPossibleMoves().push_back(piecePos + 10);
        if ((piecePos / 8) != 6) {
            if ((piecePos % 8) >= 1)
                tmpPiece->getPossibleMoves().push_back(piecePos + 15);
            if ((piecePos % 8) <= 6)
                tmpPiece->getPossibleMoves().push_back(piecePos + 17);
        }
    }

    tmpPiece->getDangerMoves().clear();

    for (int i = 0; i < tmpPiece->getPossibleMoves().size(); i++) {

        if (!p_Turn) {
            if ((tmpPiece->getPossibleMoves().at(i)) == blackPieces[3].getPosition())
                tmpPiece->getDangerMoves().push_back(tmpPiece->getPossibleMoves().at(i));
        }
        else {
            if ((tmpPiece->getPossibleMoves().at(i)) == whitePieces[4].getPosition())
                tmpPiece->getDangerMoves().push_back(tmpPiece->getPossibleMoves().at(i));
        }

    }

    tmpPiece->getDangerMoves().push_back(tmpPiece->getPosition());

}


void GameLogic::calc_pawn_Moves(Pieces* tmpPiece) {


    tmpPiece->getPossibleMoves().clear();

    int piecePos{ tmpPiece->getPosition() };

    if (tmpPiece->getcolour()) { // If pawn is white
        if ((piecePos / 8) != 0) {
            int i{ 0 };
            for (i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos - 8)) || (blackPieces[i].getPosition() == (piecePos - 8)))
                    break;
            }
            if ((i == 16) && p_Turn) {
                tmpPiece->getPossibleMoves().push_back(piecePos - 8);

                if (!tmpPiece->getMove()) {
                    for (i = 0; i < 16; i++) {
                        if ((whitePieces[i].getPosition() == (piecePos - 16)) || (blackPieces[i].getPosition() == (piecePos - 16)))
                            break;
                    }
                    if (i == 16)
                        tmpPiece->getPossibleMoves().push_back(piecePos - 16);
                }
            }

            if ((piecePos % 8) != 0) {
                for (i = 0; i < 16; i++) {
                    if (!p_Turn || (blackPieces[i].getPosition() == (piecePos - 9)) || (whitePieces[i].getPosition() == (piecePos - 9))) {
                        tmpPiece->getPossibleMoves().push_back(piecePos - 9);
                        break;
                    }
                    else if ((blackPieces[i].getenpassant() == (piecePos - 9)) && (blackPieces[i].getenpassant() != -1)) {
                        tmpPiece->getPossibleMoves().push_back(piecePos - 9);
                        break;
                    }
                }
            }

            if ((piecePos % 8) != 7) {
                for (i = 0; i < 16; i++) {
                    if (!p_Turn || (blackPieces[i].getPosition() == (piecePos - 7)) || (whitePieces[i].getPosition() == (piecePos - 7))) {
                        tmpPiece->getPossibleMoves().push_back(piecePos - 7);
                        break;
                    }
                    else if ((blackPieces[i].getenpassant() == (piecePos - 7)) && (blackPieces[i].getenpassant() != -1)) {
                        tmpPiece->getPossibleMoves().push_back(piecePos - 7);
                        break;
                    }
                }
            }

        }
        else { // MUST PROMOTE PAWN
            tmpPiece->setPiece('Q', tmpPiece->getcolour(), tmpPiece->getPosition(), true);
            calc_queen_Moves(tmpPiece);
            return;
        }


    }
    else { //if pawn is black

        if ((piecePos / 8) != 7) {
            int i{ 0 };
            for (i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == (piecePos + 8)) || (blackPieces[i].getPosition() == (piecePos + 8)))
                    break;
            }
            if ((i == 16) && !p_Turn) {
                tmpPiece->getPossibleMoves().push_back(piecePos + 8);

                if (!tmpPiece->getMove()) {
                    for (i = 0; i < 16; i++) {
                        if ((whitePieces[i].getPosition() == (piecePos + 16)) || (blackPieces[i].getPosition() == (piecePos + 16)))
                            break;
                    }
                    if (i == 16)
                        tmpPiece->getPossibleMoves().push_back(piecePos + 16);
                }
            }

            if ((piecePos % 8) != 0) {
                for (i = 0; i < 16; i++) {
                    if (p_Turn || (whitePieces[i].getPosition() == (piecePos + 7)) || (blackPieces[i].getPosition() == (piecePos + 7))) {
                        tmpPiece->getPossibleMoves().push_back(piecePos + 7);
                        break;
                    }
                    else if ((whitePieces[i].getenpassant() == (piecePos + 7)) && (whitePieces[i].getenpassant() != -1)) {
                        tmpPiece->getPossibleMoves().push_back(piecePos + 7);
                        break;
                    }
                }
            }

            if ((piecePos % 8) != 7) {
                for (i = 0; i < 16; i++) {
                    if (p_Turn || (whitePieces[i].getPosition() == (piecePos + 9)) || (blackPieces[i].getPosition() == (piecePos + 9))) {
                        tmpPiece->getPossibleMoves().push_back(piecePos + 9);
                        break;
                    }
                    else if ((whitePieces[i].getenpassant() == (piecePos + 9)) && (whitePieces[i].getenpassant() != -1)) {
                        tmpPiece->getPossibleMoves().push_back(piecePos + 9);
                        break;
                    }
                }
            }

        }
        else { // MUST PROMOTE PAWN
            tmpPiece->setPiece('Q', tmpPiece->getcolour(), tmpPiece->getPosition(), true);
            calc_queen_Moves(tmpPiece);
            return;
        }
    }

    tmpPiece->getDangerMoves().clear();

    for (int i = 0; i < tmpPiece->getPossibleMoves().size(); i++) {

        if (!p_Turn) {
            if ((tmpPiece->getPossibleMoves().at(i)) == blackPieces[3].getPosition())
                tmpPiece->getDangerMoves().push_back(tmpPiece->getPossibleMoves().at(i));
        }
        else {
            if ((tmpPiece->getPossibleMoves().at(i)) == whitePieces[4].getPosition())
                tmpPiece->getDangerMoves().push_back(tmpPiece->getPossibleMoves().at(i));
        }

    }

    tmpPiece->getDangerMoves().push_back(tmpPiece->getPosition());

}


void GameLogic::calc_Castle_Moves(Pieces* tmpPiece) {

    if (Checkp_Turn || (tmpPiece->getname() != 'K') || tmpPiece->getMove() || (tmpPiece->getcolour() != p_Turn))
        return;


    if (tmpPiece->getcolour()) { // If White King
        // whitePieces[0] Bot Left Rook, whitePieces[7] Bot Right Rook
        if (!whitePieces[7].getMove()) {
            int i{ 0 };
            for (i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == 61) || (whitePieces[i].getPosition() == 62)) {
                    i = 17;
                    break;
                }
                if ((blackPieces[i].getPosition() == 61) || (blackPieces[i].getPosition() == 62)) {
                    i = 17;
                    break;
                }
            }
            if (i == 16) {
                for (i = 0; i < 16; i++) {
                    for (int j = 0; j < blackPieces[i].getPossibleMoves().size(); j++) {
                        if ((blackPieces[i].getPossibleMoves().at(j) == 61) || (blackPieces[i].getPossibleMoves().at(j) == 62) || (blackPieces[i].getPossibleMoves().at(j) == 60)) {
                            i = 17;
                            break;
                        }
                    }
                    if (i == 17) break;
                }
            }
            if (i != 17) {

                tmpPiece->getPossibleMoves().push_back(62);
            }
        }

        if (!whitePieces[0].getMove()) {
            int i{ 0 };
            for (i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == 57) || (whitePieces[i].getPosition() == 58) || (whitePieces[i].getPosition() == 59)) {
                    i = 17;
                    break;
                }
                if ((blackPieces[i].getPosition() == 57) || (blackPieces[i].getPosition() == 58) || (blackPieces[i].getPosition() == 59)) {
                    i = 17;
                    break;
                }
            }
            if (i == 16) {
                for (i = 0; i < 16; i++) {
                    for (int j = 0; j < blackPieces[i].getPossibleMoves().size(); j++) {
                        if ((blackPieces[i].getPossibleMoves().at(j) == 58) || (blackPieces[i].getPossibleMoves().at(j) == 59) || (blackPieces[i].getPossibleMoves().at(j) == 60)) {
                            i = 17;
                            break;
                        }
                    }
                    if (i == 17) break;
                }
            }
            if (i != 17) {
                tmpPiece->getPossibleMoves().push_back(58);
            }
        }
    }
    else { // If Black King
        // blackPieces[7] Top Left Rook, blackPieces[0] Top Right Rook
        if (!blackPieces[7].getMove()) {
            int i{ 0 };
            for (i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == 3) || (whitePieces[i].getPosition() == 2) || (whitePieces[i].getPosition() == 1)) {
                    i = 17;
                    break;
                }
                if ((blackPieces[i].getPosition() == 3) || (blackPieces[i].getPosition() == 2) || (blackPieces[i].getPosition() == 1)) {
                    i = 17;
                    break;
                }
            }
            if (i == 16) {
                for (i = 0; i < 16; i++) {
                    for (int j = 0; j < whitePieces[i].getPossibleMoves().size(); j++) {
                        if ((whitePieces[i].getPossibleMoves().at(j) == 3) || (whitePieces[i].getPossibleMoves().at(j) == 2) || (whitePieces[i].getPossibleMoves().at(j) == 4)) {
                            i = 17;
                            break;
                        }
                    }
                    if (i == 17) break;
                }
            }
            if (i != 17) {
                tmpPiece->getPossibleMoves().push_back(2);
            }
        }

        if (!blackPieces[0].getMove()) {
            int i{ 0 };
            for (i = 0; i < 16; i++) {
                if ((whitePieces[i].getPosition() == 5) || (whitePieces[i].getPosition() == 6)) {
                    i = 17;
                    break;
                }
                if ((blackPieces[i].getPosition() == 5) || (blackPieces[i].getPosition() == 6)) {
                    i = 17;
                    break;
                }
            }
            if (i == 16) {
                for (i = 0; i < 16; i++) {
                    for (int j = 0; j < whitePieces[i].getPossibleMoves().size(); j++) {
                        if ((whitePieces[i].getPossibleMoves().at(j) == 5) || (whitePieces[i].getPossibleMoves().at(j) == 6) || (whitePieces[i].getPossibleMoves().at(j) == 4)) {
                            i = 17;
                            break;
                        }
                    }
                    if (i == 17) break;
                }
            }
            if (i != 17) {
                tmpPiece->getPossibleMoves().push_back(6);
            }
        }
    }
}


void GameLogic::checkMate() {
    // No more than two piece can check a King.
    // A single check can be unchecked either by the King moving to
        // a square that is not attacked, or if another piece blocks/kills the attacking piece
    // A double check can be unchecked only by moving the checked King

    Pieces* check1{ NULL };
    Pieces* check2{ NULL };

    // Check if current player's King is in check
    // whitePieces[4] is white King , blackPieces[3] is black King
    for (int i = 0; i < 16; i++) {
        if (p_Turn) { // White turn
            for (int j = 0; j < blackPieces[i].getPossibleMoves().size(); j++) {
                if (whitePieces[4].getPosition() == blackPieces[i].getPossibleMoves().at(j)) {
                    if (check1 == NULL) {
                        Checkp_Turn = true;
                        check1 = &blackPieces[i];
                        break;
                    }
                    else if (check2 == NULL) {
                        //playerTurnCheck = true;
                        check2 = &blackPieces[i];
                        break;
                    }
                }
            }
        }
        else { // Black turn
            for (int j = 0; j < whitePieces[i].getPossibleMoves().size(); j++) {
                if (blackPieces[3].getPosition() == whitePieces[i].getPossibleMoves().at(j)) {
                    if (check1 == NULL) {
                        Checkp_Turn = true;
                        check1 = &whitePieces[i];
                        break;
                    }
                    else if (check2 == NULL) {
                        //playerTurnCheck = true;
                        check2 = &whitePieces[i];
                        break;
                    }
                }
            }
        }

        if (check2 != NULL)
            break;
    }

    // Check which current player pieces moves put its King out of check
    // If no moves then Check Mate, current player loses
    if (Checkp_Turn) {
        if (check2 != NULL) { // If double check, clear current player's pieces moves except king's
            if (p_Turn)
                for (int i = 0; i < 16; i++)
                    if (whitePieces[i].getname() != 'K')
                        whitePieces[i].getPossibleMoves().clear();
                    else
                        for (int i = 0; i < 16; i++)
                            if (blackPieces[i].getname() != 'K')
                                blackPieces[i].getPossibleMoves().clear();
        }
        else { // If single check

            for (int j = 0; j < 16; j++) { // pieces array counter
                std::vector<int> tmpMoves;

                if (p_Turn) { // If White turn
                    if (whitePieces[j].getname() == 'K')
                        continue;
                    for (int o = 0; o < whitePieces[j].getPossibleMoves().size(); o++) {
                        if (whitePieces[j].getPossibleMoves().empty())
                            break;
                        for (int i = 0; i < check1->getDangerMoves().size(); i++) { // Checking piece moves counter
                            if ((whitePieces[j].getPossibleMoves().at(o) == check1->getDangerMoves().at(i))) {
                                tmpMoves.push_back(whitePieces[j].getPossibleMoves().at(o));
                                break;
                            }
                        }
                    }

                    whitePieces[j].getPossibleMoves().clear();
                    whitePieces[j].getPossibleMoves() = tmpMoves;
                }
                else { // If Black turn
                    if (blackPieces[j].getname() == 'K')
                        continue;
                    for (int o = 0; o < blackPieces[j].getPossibleMoves().size(); o++) {
                        if (blackPieces[j].getPossibleMoves().empty())
                            break;
                        for (int i = 0; i < check1->getDangerMoves().size(); i++) { // Checking piece moves counter
                            if ((blackPieces[j].getPossibleMoves().at(o) == check1->getDangerMoves().at(i))) {
                                tmpMoves.push_back(blackPieces[j].getPossibleMoves().at(o));
                                break;
                            }
                        }
                    }
                    blackPieces[j].getPossibleMoves().clear();
                    blackPieces[j].getPossibleMoves() = tmpMoves;
                }
            }
        }


        //Bug fix
        // whitePieces[4] is white King , blackPieces[3] is black King
        Pieces* curKing;
        if (p_Turn) {
            curKing = &whitePieces[4];
        }
        else {
            curKing = &blackPieces[3];
        }
        if (check1 != NULL) {
            if ((check1->getname() == 'Q') || (check1->getname() == 'R' || (check1->getname() == 'B'))) {
                int checkPos{ check1->getPosition() };

                if ((check1->getname() == 'Q') || (check1->getname() == 'R')) {
                    for (int i = 0; i < curKing->getPossibleMoves().size(); i++) {
                        if (curKing->getPossibleMoves().at(i) != checkPos) {
                            if ((curKing->getPossibleMoves().at(i) % 8) == (checkPos % 8))
                                curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                            else if ((curKing->getPossibleMoves().at(i) / 8) == (checkPos / 8))
                                curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                        }
                    }
                }

                for (int i = 0; i < curKing->getPossibleMoves().size(); i++) {
                    if (curKing->getPossibleMoves().at(i) != checkPos) {
                        if ((curKing->getPosition() % 8) < (checkPos % 8)) { // King left of Check
                            if ((curKing->getPosition() / 8) < (checkPos / 8)) { // King top of Check
                                if (((curKing->getPossibleMoves().at(i) % 8) < (curKing->getPosition() % 8)) && ((curKing->getPossibleMoves().at(i) / 8) < (curKing->getPosition() / 8)))
                                    curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                            }
                            else if ((checkPos / 8) < (curKing->getPosition() / 8)) { // King under Check
                                if (((curKing->getPossibleMoves().at(i) % 8) < (curKing->getPosition() % 8)) && ((curKing->getPossibleMoves().at(i) / 8) > (curKing->getPosition() / 8)))
                                    curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                            }
                        }
                        else if ((checkPos % 8) < (curKing->getPosition() % 8)) { // King right of Check
                            if ((curKing->getPosition() / 8) < (checkPos / 8)) { // King top of Check
                                if (((curKing->getPossibleMoves().at(i) % 8) > (curKing->getPosition() % 8)) && ((curKing->getPossibleMoves().at(i) / 8) < (curKing->getPosition() / 8)))
                                    curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                            }
                            else if ((checkPos / 8) < (curKing->getPosition() / 8)) { // King under Check
                                if (((curKing->getPossibleMoves().at(i) % 8) > (curKing->getPosition() % 8)) && ((curKing->getPossibleMoves().at(i) / 8) > (curKing->getPosition() / 8)))
                                    curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                            }
                        }
                    }
                }
            }
        }
        //Bug fix
        if (check2 != NULL) {
            if ((check2->getname() == 'Q') || (check2->getname() == 'R' || (check2->getname() == 'B'))) {
                int checkPos{ check2->getPosition() };

                if ((check2->getname() == 'Q') || (check2->getname() == 'R')) {
                    for (int i = 0; i < curKing->getPossibleMoves().size(); i++) {
                        if (curKing->getPossibleMoves().at(i) != checkPos) {
                            if ((curKing->getPossibleMoves().at(i) % 8) == (checkPos % 8))
                                curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                            else if ((curKing->getPossibleMoves().at(i) / 8) == (checkPos / 8))
                                curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                        }
                    }
                }

                for (int i = 0; i < curKing->getPossibleMoves().size(); i++) {
                    if (curKing->getPossibleMoves().at(i) != checkPos) {
                        if ((curKing->getPosition() % 8) < (checkPos % 8)) { // King left of Check
                            if ((curKing->getPosition() / 8) < (checkPos / 8)) { // King top of Check
                                if (((curKing->getPossibleMoves().at(i) % 8) < (curKing->getPosition() % 8)) && ((curKing->getPossibleMoves().at(i) / 8) < (curKing->getPosition() / 8)))
                                    curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                            }
                            else if ((checkPos / 8) < (curKing->getPosition() / 8)) { // King under Check
                                if (((curKing->getPossibleMoves().at(i) % 8) < (curKing->getPosition() % 8)) && ((curKing->getPossibleMoves().at(i) / 8) > (curKing->getPosition() / 8)))
                                    curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                            }
                        }
                        else if ((checkPos % 8) < (curKing->getPosition() % 8)) { // King right of Check
                            if ((curKing->getPosition() / 8) < (checkPos / 8)) { // King top of Check
                                if (((curKing->getPossibleMoves().at(i) % 8) > (curKing->getPosition() % 8)) && ((curKing->getPossibleMoves().at(i) / 8) < (curKing->getPosition() / 8)))
                                    curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                            }
                            else if ((checkPos / 8) < (curKing->getPosition() / 8)) { // King under Check
                                if (((curKing->getPossibleMoves().at(i) % 8) > (curKing->getPosition() % 8)) && ((curKing->getPossibleMoves().at(i) / 8) > (curKing->getPosition() / 8)))
                                    curKing->getPossibleMoves().erase(curKing->getPossibleMoves().begin() + i--);
                            }
                        }
                    }
                }
            }
        }

    }
    else {
        calc_Castle_Moves(&whitePieces[4]);
        calc_Castle_Moves(&blackPieces[3]);
    }

    // Check if current player has any available moves
    int i{ 0 };
    for (i = 0; i < 16; i++) {
        if (p_Turn) {
            if (!whitePieces[i].getPossibleMoves().empty())
                break;
        }
        else {
            if (!blackPieces[i].getPossibleMoves().empty())
                break;
        }
    }
    if (i == 16) {
        mates = true;
    }

}

chessboard::chessboard(sf::Color col1, sf::Color col2) {
    load(col1, col2);
}

// Member function that sets Board stuff, can choose square colors in parameters
void chessboard::load(sf::Color col1, sf::Color col2) {
    for (int i = 0; i < 8; i++) {

        bool tmpColor = ((i % 2) == 0) ? true : false;

        for (int j = 0; j < 8; j++) {

            m_boardSquares[j + (i * 8)].setPosition(sf::Vector2f(j * 64.f, i * 64.f));
            m_boardSquares[j + (i * 8)].setSize(sf::Vector2f(64.f, 64.f));
            m_boardSquares[j + (i * 8)].setFillColor(tmpColor ? col1 : col2);

            tmpColor = !tmpColor;
        }
    }
}

// Draw class on SFML Window
void chessboard::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int i = 0; i < 64; i++) {
        target.draw(m_boardSquares[i]);
    }
}

int main() {
    GameLogic chess(sf::Color(0xf3bc7aff), sf::Color(0xae722bff));

    sf::RenderWindow window(sf::VideoMode(768, 512), "Chess", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if ((0 <= event.mouseButton.x) && (event.mouseButton.x <= 512) && (0 <= event.mouseButton.y) && (event.mouseButton.y <= 512)) {
                        unsigned int buttonPos{ (event.mouseButton.x / 64) + ((event.mouseButton.y / 64) * (8 * (512 / window.getSize().y))) };

                        if (!chess.getSelected())
                            chess.selectPiece(buttonPos);
                        else
                            chess.moveSelected(buttonPos);
                    }
                    else if ((517 <= event.mouseButton.x) && (event.mouseButton.x <= 763) && (5 <= event.mouseButton.y) && (event.mouseButton.y <= 45)) {
                        chess.restartgame();
                    }
                }
            }
        }

        window.draw(chess);
        window.display();
    }
}