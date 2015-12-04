# Solaneae
Solaneae (solan-ee-I) is a modular open source firmware for Arduino. It features a dynamic menu system, and a task management system. It is designed for a text based display, for example the common 2x16 text display. It come packaged with the excellent LiquidCrystal replacement library by Francisco Malpartida allowing the usage of I2C displays.

Solaneae is not a library, it's a framework that includes _your_ code, as opposed to a library that is included into your code. This is called an inversion of control. Solaneae works by including modules into the main program and running them. Each module can have one or more background task that is always running, and optionally UI menu entries and interactive UI entries.

### Feature highlights

* Object oriented and modular design.
* Run multiple tasks in the background.
* "Functioniod" based callback system allowing you to mix callback into classes.
* Dynamic UI system with easy to use syntax slightly inspired by jquery.
* Submenus.
* Interactive menu items using UI callbacks.
* Each menu line can be interactive

## planned
* On-demand submenus to save ram usage.
* Wifi support
* Settings registry
* Serial/internet settings tether
* Dynanic module enable/disable at runtime!
* Widgets


**This readme is under construction. Solaneae is currently in an alpha state!**

# Building
Use the eclipse arduino plugin (v2.3 only), follow the setup instructions, and finally clone the project into your workspace.
*only tested on an Arduino UNO*

# License 
Currently the license is GPL, this is subject to change however. By contributing to this repository you give me permission to change the license with or without permission.

# API/reference

## Modules

Modules are where you write all your code, they are located in the `mod` folder and included into the `modulemanifest.h` file. Each module should have a class (or more) and a non-member setup function that instantiates the class(es) in the module. A module can contain many module classes making a module pack see `examplemodule.h`.

####Module example 2
Example of a module with a background task and a callback mixin
###### mod/example/MyModule.h
	#include "../base/modulebase.h"//include the base classes
	#include "sol/ui.h"//include the UI class
	
	namespace example_module { //it's best if module headers are in their own namespace
		class MyModule:
				public Module,//include the module base
				public UIcallbackTimer,//include a mixin for adding a UI callback(optional)
				public Spin::Task //include the background task base(optional)
				{
		public:
			MyModule();
			void callback(sol::menucallbackinfo_t &);//your UI callback
			void task();//Your background task
		};
	
		void setup();
	}//end of namespace

###### mod/example/MyModule.cpp
	#include "MyModule.h"
	namespace example_module {
		MyModule::MyModule() :UIcallbackTimer(1000) /*pass the refresh rate to the UI callback mixin*/ {
			ui.PushItem(F("MyModule"));//push a line with text into the menu
			ui.PushItem(F("says "), this);//push a line with a static label and a dynamic label written by the callback.
			alloc(10);//allocate a 10 char string for the UI callback
		}
		void MyModule::task() {
			//this will be called over and over in a loop
			//do NOT use delay(), use Timer instead!!!
		}
		void MyModule::callback(sol::menucallbackinfo_t &) {//UIcallback
			text_store = "hello";//set the dynamic label text
			ui.UpdateLine(); //tell the ui to update the line
		}
		void setup() {
			//this is the setup function for the whole module.
			//It creates an instance of the module class and runs other setup code. All we do in this example is create an instance of the module class though.
			MyModule *mod = new MyModule();//create an instance of the module that won't go away after this function exits.
		}

	}//ns end
###### mod/modulemanifest.h
	//...
	#include "example/MyModule.h"//include the module
	void module_setup() {
		//...
		//call the setup function from the included module
		example_module::setup();
	}

## Utilities

### Timer

####Basic usage


	#include "sol/timer.h" //include the timer
	
	Timer timer; //timer object
	//assume this function is called repeatedly in a loop
	void examplecallback() {
		if (timer.Every(100)) {
			//this will be called every 100ms
		}
	}


For most situations you only need to use the Every() method in Timer, however there are other methods available. Check timer.h for details.

###Print macros

These are just shortcuts if you have many debugging print statements

	#define P(thing) Serial.print(thing) //print thing
	#define PL(thing) Serial.println(thing) //print line
	#define PF(string) Serial.print(F(string)) //print flash string
	#define PLF(string) Serial.println(F(string)) //print flash string with newline