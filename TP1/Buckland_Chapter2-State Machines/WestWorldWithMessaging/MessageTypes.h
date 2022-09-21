#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_BobIsEnteringTheSaloon,
  Msg_IApologize,
  Msg_Fight,
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case 0:
    
    return "HiHoneyImHome"; 

  case 1:
    
    return "StewReady";

  case 2:

      return "BobIsEnteringTheSaloon";

  case 3:

      return "IApologize";

  case 4:

      return "Fight";

  default:

    return "Not recognized!";
  }
}

#endif