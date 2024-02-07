#include <cstdlib> 
#include <ctime> 
#include <iostream>

using namespace std;


class Character 
{
public:
    virtual bool ChooseTarget()=0;
    void SetIsDead(bool state);
    bool GetIsDead();
protected:
    bool isDead=false;
};

class Player:public Character
{
public:
    bool ChooseTarget() override;
};

class AI:public Character
{
public:
    bool ChooseTarget() override;
};

class Weapon
{
public:
    Weapon();
    void Fire(Character* target);
    void IncreaseRevolveIndex();
    bool hasFired=false;

private:
    int bulletIndex;
    int currentRevolveIndex=0;
};

enum class Round 
{
    Player,
    AI
};

int main()
{
    Weapon* weapon = new Weapon();
    Character* ai = new AI();
    Character* player = new Player();
    Character* target;

    bool isGameCountiune = true;

    Round currentRound = Round::Player; // Assuming first round is always player
    
    while (isGameCountiune)
    {
        if (currentRound == Round::Player)
        {
            const bool shootSelf = player->ChooseTarget();
            target = shootSelf ? player : ai;
            weapon->Fire(target);
            currentRound = shootSelf ? Round::Player : Round::AI; 
        }

        else
        {
           const bool shootSelf = ai->ChooseTarget();
           target = shootSelf ? ai : player ;
           weapon->Fire(target);
           currentRound = shootSelf ? Round::AI: Round::Player;
        }

        if(!weapon->hasFired)
            weapon->IncreaseRevolveIndex();
        
        else
        {                 
            if (ai->GetIsDead())
            {
                cout << "\nCongrats! You won!";
            }
            else
            {
                cout << "\nYour rival won!";
            }
            isGameCountiune = false;
        }
    }

    cout << "\nThank you for playing";

    

}

Weapon::Weapon()
{
    srand((unsigned)time(0));
    bulletIndex = rand() % 7;
}

void Weapon::Fire(Character* target)
{
    if (this->bulletIndex == this->currentRevolveIndex)
    {
        cout << "\nBum! Gun fired!";
        this->hasFired = true;
        target->SetIsDead(true);
    }
    else
    {
        cout << "\nClick... It's empty.";
    }
}

void Weapon::IncreaseRevolveIndex()
{
    this->currentRevolveIndex++;
}

bool AI::ChooseTarget()
{
    srand((unsigned)time(0));
    const int choice = rand() % 2;
    if (choice == 1)
    {
        cout << "\nYour rival decided to shoot itself";
    }
    else 
    {
        cout << "\nYour rival decided to shoot you";
    }
    return choice;
}

void Character::SetIsDead(bool state)
{
    this->isDead = state;
}

bool Character::GetIsDead()
{
    return this->isDead;
}

bool Player::ChooseTarget()
{
    cout << "\nIf you want to shoot rival enter 0. If you want to shoot yourself enter 1: ";
    int choice;
    cin >> choice;

    while (choice != 0 && choice != 1)
    {
        cout << "\nYou have entered invalid number. Please read again and enter a proper number";
    }

    return choice;
}
