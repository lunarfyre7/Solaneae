/*
 * modulebase.h
 *
 *  Created on: Aug 4, 2015
 *      Author: Jake Vandereay
 */

#ifndef MODULEBASE_H_
#define MODULEBASE_H_
#include <iterator>
#include <list>
#include "config.h"
#include "sol/ui.h"
#include "sol/spin.h"
//#include "Modulereg.h"
extern sol::UI ui;
//using namespace sol;
//#define wrapCB(name,obj) void name(UI_t::menucallbackinfo_t& info, char** text) {obj.ui_callback(info, text);}//make callback wrapper
//#define _makeCB(wrap,class,objname, method) class objname; void wrap(UI_t::menucallbackinfo_t& info, char** text) {objname.method(info, text);}
//#define makeCB(wrap,class,method) _makeCB(wrap, class, UNIQUE_NAME(class##method), method) ///usage makeCB(mycallback, mymodule, mymethod)

//note: this only uses 4 bytes of ram by itself (not allocating ram for the label string)

class Module : public Spin::Task { //TODO add non ui background callbacks
public:
	Module();
	virtual ~Module();
	void ui_callback_proxy(sol::UI_t::menucallbackinfo_t& info, char** text, uint8_t selector); //calls the callback in the ui, selector selects the callback number
	virtual void ui_callback(sol::UI_t::menucallbackinfo_t& info) {}; //ui  callback
	virtual void ui_callback2(sol::UI_t::menucallbackinfo_t& info) {}; //2nd ui  callback
	virtual void ui_callback3(sol::UI_t::menucallbackinfo_t& info) {}; //etc...
	virtual void ui_callback4(sol::UI_t::menucallbackinfo_t& info) {};
	virtual void ui_callback5(sol::UI_t::menucallbackinfo_t& info) {};
	virtual void ui_callback6(sol::UI_t::menucallbackinfo_t& info) {};
	virtual void task() {} //background/non-ui task
//	void setup_all(); //loop though instances and run all setup methods. Use module_reg instead
//	MenuItemCallback ext_wrapper;
protected:
	static uint8_t STR_COUNT;//CONFIG: number of callbacks
	sol::Timer timer;
//	static std::list<Module_base*> instances; //list of instances
	char **text; //pointer for ui dynamic text.
	//char *text_str; //storage for dynamic text. It really might be a good idea to use std::string instead, though this might be lighter possibly
	char *text_store[10];//array of test string pointers like the above

	void alloc(uint8_t len, uint8_t which=1);//call from constructor if using ui callback. len is the length of the ui string
	void regTask();//call from constructor if using tick callback
	void ptrset(char **, uint8_t index);//points the text pointer pointer to the string pointer.
};
//extern std::list<Module*> sol::moduleTaskList; //list of instances. Wont work as a static member for some reason.

#endif /* MODULEBASE_H_ */
