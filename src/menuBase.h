/* -*- C++ -*- */
#pragma once

struct Item;
struct MenuOut;

//////////////////////////////////////////////////////////
// roles -----------------
enum class Roles {Title,Item,Menu,Panel,Pad};

template<Roles role,typename O,void (MenuOut::*f)(bool)>
struct Role:public O {
  using O::O;
  inline void out(MenuOut&);
  inline void fmt(MenuOut& o,bool io);
};

//bind output to existing device
template<typename Dev, Dev& dev, typename O>
struct OutDev:public O {
  // inline void out(Item& i) override {i.out()}
  static inline void raw(const char*i) {dev<<i;}
  static inline void raw(char i) {dev<<i;}
  static inline void raw(unsigned char i) {dev<<i;}
};

//////////////////////////////////////////////////////////////////
// code ------------------------------------------
template<Roles role,typename O,void (MenuOut::*f)(bool)>
void Role<role,O,f>::out(MenuOut&o) {
  fmt(o,true);
  O::out(o);
  fmt(o,false);
}

template<Roles role,typename O,void (MenuOut::*f)(bool)>
inline void Role<role,O,f>::fmt(MenuOut& o,bool io) {
  (static_cast<MenuOut&>(o).*f)(io);
}
