/*
  GEMItem - menu item for GEM library.

  GEM (a.k.a. Good Enough Menu) - Arduino library for creation of graphic multi-level menu with
  editable menu items, such as variables (supports int, byte, boolean, char[17] data types) and
  option selects. User-defined callback function can be specified to invoke when menu item is saved.
  
  Supports buttons that can invoke user-defined actions and create action-specific
  context, which can have its own enter (setup) and exit callbacks as well as loop function.

  Requires AltSerialGraphicLCD library by Jon Green (http://www.jasspa.com/serialGLCD.html).
  LCD screen must be equipped with SparkFun Graphic LCD Serial Backpack and properly set up
  to operate using firmware provided with aforementioned library.

  For documentation visit:
  https://github.com/Spirik/GEM

  Created by Alexander 'Spirik' Spiridonov, 6 August 2017
  
  This is free software. You can redistribute it and/or modify it under
  the terms of Creative Commons Attribution-ShareAlike 4.0 International License.
  To view a copy of this license, visit https://creativecommons.org/licenses/by-sa/4.0/
*/

#ifndef HEADER_GEMITEM
#define HEADER_GEMITEM

// Macro constants (aliases) for menu item types
#define GEM_ITEM_VAL 0     // Menu item represents associated variable
#define GEM_ITEM_LINK 1    // Menu item represents link to another menu page
#define GEM_ITEM_BACK 2    // Menu item represents Back button (that links to parent level menu page)
#define GEM_ITEM_BUTTON 3  // Menu item represents button (that leads to execution of user-defined routine in its own context)

// Macro constant (alias) for readonly modifier of associated with menu item variable
#define GEM_READONLY true

// Forward declaration of necessary classes
class GEM;
class GEMPage;
class GEMSelect;

// Declaration of GEMItem class
class GEMItem {
  friend class GEM;
  friend class GEMPage;
  public:
    /* 
      Constructor for menu item that represents option select, w/ callback
      @param 'title_' - title of the menu item displayed on the screen
      @param 'linkedVariable_' - pointer to variable that menu item is associated with
      @param 'linkedType_' - type of the associated variable
      values GEM_VAL_INTEGER, GEM_VAL_BYTE, GEM_VAL_CHAR, GEM_VAL_BOOLEAN, GEM_VAL_SELECT
      @param 'select_' - pointer to GEMSelect option select
      @param 'saveAction_' - pointer to callback function exectuted when associated variable is successfuly saved
    */
    GEMItem(char* title_, void* linkedVariable_, byte linkedType_, GEMSelect* select_, void (*saveAction_)());
    /* 
      Constructor for menu item that represents option select, w/o callback
      @param 'title_' - title of the menu item displayed on the screen
      @param 'linkedVariable_' - pointer to variable that menu item is associated with
      @param 'linkedType_' - type of the associated variable
      values GEM_VAL_INTEGER, GEM_VAL_BYTE, GEM_VAL_CHAR, GEM_VAL_BOOLEAN, GEM_VAL_SELECT
      @param 'select_' - pointer to GEMSelect option select
    */
    GEMItem(char* title_, void* linkedVariable_, byte linkedType_, GEMSelect* select_);
    /* 
      Constructor for menu item that represents variable, w/ callback
      @param 'title_' - title of the menu item displayed on the screen
      @param 'linkedVariable_' - pointer to variable that menu item is associated with
      @param 'linkedType_' - type of the associated variable
      values GEM_VAL_INTEGER, GEM_VAL_BYTE, GEM_VAL_CHAR, GEM_VAL_BOOLEAN
      @param 'saveAction_' - pointer to callback function exectuted when associated variable is successfuly saved
    */
    GEMItem(char* title_, void* linkedVariable_, byte linkedType_, void (*saveAction_)());
    /* 
      Constructor for menu item that represents variable, w/o callback
      @param 'title_' - title of the menu item displayed on the screen
      @param 'linkedVariable_' - pointer to variable that menu item is associated with
      @param 'linkedType_' - type of the associated variable
      values GEM_VAL_INTEGER, GEM_VAL_BYTE, GEM_VAL_CHAR, GEM_VAL_BOOLEAN
      @param 'readonly_' (optional) - set readonly mode for variable that menu item is associated with
      values GEM_READONLY (alias for true)
      default false
    */
    GEMItem(char* title_, void* linkedVariable_, byte linkedType_, boolean readonly_ = false);
    /* 
      Constructor for menu item that represents link to another menu page
      @param 'title_' - title of the menu item displayed on the screen
      @param 'linkedPage_' - pointer to GEMPage menu page that menu item is associated with
    */
    GEMItem(char* title_, GEMPage* linkedPage_);
    /* 
      Constructor for menu item that represents button
      @param 'title_' - title of the menu item displayed on the screen
      @param 'buttonAction__' - pointer to function that will be executed when menu item is activated
    */
    GEMItem(char* title_, void (*buttonAction_)());
    void setReadonly(boolean mode = true);  // Explicitly set or unset readonly mode for variable that menu item is associated with
                                            // (relevant for GEM_VAL_INTEGER, GEM_VAL_BYTE, GEM_VAL_CHAR, GEM_VAL_BOOLEAN variables)
    boolean getReadonly();                  // Get readonly state for variable that menu item is associated with
  private:
    char* title;
    byte type;
    void* linkedVariable;
    byte linkedType;
    boolean readonly = false;
    GEMSelect* select;
    GEMPage* linkedPage;
    GEMItem* menuItemNext;
    void (*buttonAction)();
    void (*saveAction)();
};
  
#endif