/***
* Author: Stasiek Fortoński
* Date: 06.07.2017
* Group System
* Version: 2
***/

#ifndef GROUP_HPP
#define GROUP_HPP 1
#include <random>
#include "../stats/stats.hpp"
#include "../characters/player/player.hpp"
#include "../characters/npc/npc.hpp"

class Group
{
    static const unsigned MAXSIZE = 10;
    Stats * mate[MAXSIZE];
    unsigned amount = 0;

    unsigned playerTargetContoler(const Group & grp);
    unsigned npcTargetControler(const Group & grp);

public:
  Group(){
      for (unsigned i = 0; i < MAXSIZE; ++i)
        mate[i] = nullptr;
  }

  Group(const Group & grp)
  {
      for (unsigned i = 0; i < MAXSIZE; ++i)
      {
          if (grp.mate[i] != nullptr)
          {
              if (player_cast(grp.mate[i]) != nullptr)
                 mate[i] = new Player(*grp.mate[i]);
              else mate[i] = new NonPlayerCharacter(*grp.mate[i]);
          }
          else mate[i] = nullptr;
      }
      amount = grp.amount;
  }

  Group(Group && grp)
  {
      for (unsigned i = 0; i < MAXSIZE; ++i)
      {
          mate[i] = grp.mate[i];
          grp.mate[i] = nullptr;
      }
      amount = grp.amount;
      grp.amount = 0;
  }

  Group & operator=(const Group & grp)
  {
      if (&grp == this) return *this;

      for (unsigned i = 0; i < MAXSIZE; ++i)
      {
          if (grp.mate[i] != nullptr)
          {
              if (player_cast(grp.mate[i]) != nullptr)
                 mate[i] = new Player(*grp.mate[i]);
              else mate[i] = new NonPlayerCharacter(*grp.mate[i]);
          }
          else mate[i] = nullptr;
      }
      amount = grp.amount;

      return *this;
  }


  Group & operator=(Group && grp)
  {
      if (&grp == this) return *this;

      for (unsigned i = 0; i < MAXSIZE; ++i)
      {
          mate[i] = grp.mate[i];
          grp.mate[i] = nullptr;
      }
      amount = grp.amount;
      grp.amount = 0;

      return *this;
  }

  virtual ~Group(){
      for (unsigned i = 0; i < amount; ++i)
        delete mate[i];
  }

  bool push_back(Stats * ptr);
  void pop_back();
  void pop_back(const unsigned & n);
  void sort();
  void random();
  bool allIsDeath() const;
  void regenerations();

  bool empty(){return amount == 0;}
  bool full(){return amount == MAXSIZE;}

  unsigned size() const{return amount;}
  unsigned max_size() const{return MAXSIZE;}

  Stats * operator[](const unsigned & n){return mate[n];}
  const Stats * operator[](const unsigned & n) const{return mate[n];}

  Player * player_cast(Stats * ptr){return dynamic_cast<Player *>(ptr);};
  NonPlayerCharacter * npc_cast(Stats * ptr){return dynamic_cast<NonPlayerCharacter *>(ptr);};

  void show() const;
  void showAdd(Stats * st) const;
  unsigned target(const unsigned & n, const Group & grp);
  void controlOurTeam();
  void controlMember(const unsigned & n);
  void addControl(Stats * st);
};
#endif
