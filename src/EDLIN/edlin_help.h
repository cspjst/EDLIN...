#ifndef EDLIN_HELP_H
#define EDLIN_HELP_H

#include "edlin_types.h" 

// in token enum order
static const char EDLIN_HELP[] = {
  {"Edit line                  line#"},
  {"Line after the last line   #"},
  {"Current edit line          ."},
  {"Show help                  ?"},
  {"End (save file)            E"},
  {"Quit (throw away changes)  Q"},
  {"Append                     [#lines]A"},
  {"Copy                       [range][,times]C"},
  {"Delete                     [range]D Delete lines"},
  {"Insert                     [line]I"},
  {"List                       [range]L"},
  {"Move                       [range],tolineM"},
  {"Page                       [range]P"},
  {"Write                      [#lines]W"},
  {"Replace                    [range][?]R[old],[new]"},
  {"Search                     [range][?]S[text]"},
  {"Transfer                   [toline]Tfilepath"},
  {"Command syntax error!"},
  {"Empty input!"},
  {"Unknown command!"}
};

#endif
