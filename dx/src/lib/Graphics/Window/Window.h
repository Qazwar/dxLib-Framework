#pragma once
#include "../lib.h"
#include "../../../dx.h"
#include "../../Math/Region.h"
#include "../../Task.h"
#include "../../async.h"
#include "../BasePainter.h"

begin_UI class Component; end_UI

begin_GRAPHICS
#undef LoadIcon


/*******************************
	Window event arguments
 *******************************/

class WindowMovedArgs : public EventArgs
{
public:
	__MATH Region region;
};
using WindowResizeArgs = WindowMovedArgs;

class WindowClosingArgs : public EventArgs
{
public:
	bool ShouldClose;
};

class KeyDownArgs : public EventArgs
{
public:
	__DX uint key_code;
	bool shift, ctrl;
};

class KeyUpArgs : public EventArgs
{
public:
	__DX uint key_code;
	bool shift, ctrl;
};

class KeyDownCharArgs : public EventArgs
{
public:
	char key_char;
};

class MouseMovedArgs : public EventArgs
{
public:
	__MATH Vector2 position;
	bool shift, ctrl;
};

class MouseClickedArgs : public EventArgs
{
public:
	__DX uint key;
	__MATH Vector2 position;
	bool shift, ctrl;
};

class MouseReleasedArgs : public EventArgs
{
public:
	__DX uint key;
	__MATH Vector2 position;
	bool shift, ctrl;
};

class ScrollArgs : public EventArgs
{
public:
	enum ScrollDirection { Up, Down };
	ScrollDirection direction;
	int delta;
	bool shift, ctrl;
	inline bool up( ) { return direction == Up; }
	inline bool down( ) { return direction == Down; }
};

class MessageDataArgs : public EventArgs
{
public:
	__DX uint Msg;
	WPARAM wParam;
	LPARAM lParam;
};

class Window
{
public:
	using WindowMovedSig = void(Window*, WindowMovedArgs&);
	using WindowClosingSig = void(Window*, WindowClosingArgs&);
	using KeyDownSig = void(Window*, KeyDownArgs&);
	using KeyUpSig = void(Window*, KeyUpArgs&);
	using KeyDownCharSig = void(Window*, KeyDownCharArgs&);
	using MouseMovedSig = void(Window*, MouseMovedArgs&);
	using MouseClickedSig = void(Window*, MouseClickedArgs&);
	using MouseReleasedSig = void(Window*, MouseReleasedArgs&);
	using ScrollSig = void(Window*, ScrollArgs&);
	using MessageDataSig = void(Window*, MessageDataArgs&);

	enum PaintStyle_t
	{
		OnEvent_t,
		OnTick_t
	};

	typedef std::chrono::system_clock clock;
	typedef std::chrono::time_point<clock> time_point;


	///<summary>
	///	Creates a window.
	///</summary>
	static Window* Create( const __LIB String &_Class, 
						   const __LIB String &_Title,
						   const __MATH Region &_Region,
						   DWORD dwStyle = WS_OVERLAPPEDWINDOW,
						   DWORD dwExStyle = 0L );

	///<summary>
	///	Creates a window that is a child of _Parent
	///</summary>
	static Window* Create( Window *_Parent,
						   const __LIB String &_Class, 
						   const __LIB String &_Title,
						   const __MATH Region &_Region,
						   DWORD dwStyle = WS_OVERLAPPEDWINDOW,
						   DWORD dwExStyle = 0L );


public:
	~Window( );

public:
		// Wrappers

	///<summary>
	///	Retrieves the tile of this window.
	///</summary>
	__LIB String getTitle( );

	///<summary>
	///	Sets the title of this window.
	///</summary>
	void setTitle( const __LIB String &_Title );

	///<summary>
	///	Retrieves the class name of a window.
	///</summary>
	__LIB String getClass( );
	
	///<summary>
	///	Converts the client-area coordinates of a specified point to screen coordinates
	///</summary>
	bool ClientToScreen( __MATH Vector2 &_PointOut );
	
	///<summary>
	/// Converts the screen coordinates of a specified point on the screen to client-area coordinates
	///</summary>
	bool ScreenToClient( __MATH Vector2 &_PointOut );

	///<summary>
	///	Hides the widnow.
	///</summary>
	bool Hide( );

	///<summary>
	///	Shows the window.
	///</summary>
	bool Show( );

	///<summary>
	///	Brings the window to the top.
	///</summary>
	bool BringToTop( );

	///<summary>
	///	Minimizes the window to the taskbar.
	///</summary>
	bool Minimize( );

	///<summary>
	///	Maximizes the window.
	///</summary>
	bool Maximize( );

	///<summary>
	///	Restores the windows state.
	///</summary>
	bool Restore( );

	///<summary>
	/// Sends a new WM_PAINT message to this window, use this if you wish to repaint everything.
	/// Note that this will only work if this window PaintStyle is OnEvent_t!
	///</summary>
	bool ForcePaint( );

	///<summary>
	///	Enables the window.
	///</summary>
	bool Enable( );

	///<summary>
	///	Disables the window.
	///</summary>
	bool Disable( );

	///<summary>
	/// Load the icon showed in taskbar (32x32). 
	/// Supports bitmaps and ico's.
	///</summary>
	bool LoadIcon( const __FILEIO Path &_Path	);

	///<summary>
	/// Load the icon showed in the top left corner of the window.
	/// Supports bitmaps and ico's.
	///</summary>
	bool LoadIconSm( const __FILEIO Path &_Path );


	///<summary>
	/// Forces a closing of a window, this does NOT trigger OnWindowClosing event,
	/// this will DESTROY the window and call respective events.
	///</summary>
	void Close( );

	///<summary>
	///	Retrives the parent of the window.
	///</summary>
	__GRAPHICS Window* getParent( );

	///<summary>
	///	Changes the paint style of this window, only paint per event or paint per tick.
	///</summary>
	void SpecializePaint( const PaintStyle_t &_Style );

	///<summary>
	///	Retrives the paint style of this window.
	///</summary>
	PaintStyle_t PaintStyle( ) const;

	///<summary>
	///	Retrives the painter of the window.
	///</summary>
	__GRAPHICS BasePainter* getPainter( );

	///<summary>
	///	Sets the painter of the window.
	///</summary>
	void setPainter( __GRAPHICS BasePainter *_Painter, const bool &_Delete_Old = true );

	///<summary>
	/// Returns wether or not this window has a painter.
	///</summary>
	bool has_painter( ) const;

	///<summary>
	/// Gets the width of this window
	///</summary>
	float Width( ) const;

	///<summary>
	/// Gets the height
	///</summary>
	float Height( ) const;

	///<summary>
	/// Returns wether or not Ctrl is held
	///</summary>
	bool isCtrlHeld( ) const;

	///<summary>
	/// Returns wether or not Shift is held
	///</summary>
	bool isShiftHeld( ) const;


	///<summary>
	/// Returns the native window handle for this window.
	///</summary>
	HWND native_handle( );

public: // Others

	///<summary>
	///	Adds a task to the task queue.	
	///</summary>
	__LIB TimedTask<void(Window*)> &addTask( const time_point &_When, const std::function<void(Window*)> &_Function );

	///<summary>
	///	This windows internal event loop, called from the respective WindowProc
	/// you can call this function yourself to inject messages into the loop
	///</summary>
	LRESULT HandleInput( HWND hWnd, __DX uint Msg, WPARAM wParam, LPARAM lParam );

	///<summary>
	///	Handle all tasks that has been put on the window.
	///</summary>
	void HandleTasks( );

	///<summary>
	/// Polls all windows events and fires WindowProc.
	///</summary>
	bool PollEvents( );

	///<summary>
	/// Will automatically forward events to this component
	///</summary>
	void HandleComponent( __UI Component *_Comp );

	///<summary>
	///	Remove the handling of this component, uses the ID to determine which event handler(s) to remove.
	///</summary>
	void StopHandlingComponent( __UI Component *_Comp );

public:
		// Events

	///</summary>
	///	Called when the window is moved.
	///<summary>
	__LIB Event<void(Window*, WindowMovedArgs&)>& OnWindowMoved( );

	///<summary>
	///	Called when the window is resized
	///</summary>
	__LIB Event<void(Window*, WindowResizeArgs&)>& OnWindowResize( );
	
	///<summary>
	///	Called when the window is maximized
	///</summary>
	__LIB Event<void(Window*)>& OnWindowMaximize( );

	///<sumamry>
	/// Called when the window is restored from its minimized or maximized state.
	///</summary>
	__LIB Event<void(Window*)>& OnWindowRestored( );

	///<summary>
	///	Called when the window is minimized to the taskbar
	///</summary>
	__LIB Event<void(Window*)>& OnWindowMinimize( );

	///<summary>
	/// Called when the window is about to close, you can cancel
	/// the closing by setting WindowCloseArgs::ShouldClose to false.
	///</summary>
	__LIB Event<void(Window*, WindowClosingArgs&)>& OnWindowClosing( );

	///</summary>
	/// Called when the window is closed.
	///<summary>
	__LIB Event<void(Window*)>& OnWindowClosed( ); 

	///<summary>
	/// Called when the cursor moves
	///</summary>
	__LIB Event<void(Window*, MouseMovedArgs&)>& OnMouseMoved( );

	///<summary>
	///	Called when a mouse button is clicked once.
	///</summary>
	__LIB Event<void(Window*, MouseClickedArgs&)>& OnMouseClicked( );

	///<summary>
	///	Called when a mouse button is released from its previously clicked state.
	///</summary>
	__LIB Event<void(Window*, MouseReleasedArgs&)>& OnMouseReleased( );

	///<summary>
	///	Called when a mouse button is double clicked
	///</summary>
	__LIB Event<void(Window*, MouseClickedArgs&)>& OnMouseDoubleClicked( );

	///<summary>
	/// Called when the mouse wheel is scrolled.
	///</summary>
	__LIB Event<void(Window*, ScrollArgs&)>& OnScroll( );

	///<summary>
	///	Called once for the first key stroke, then continuously called with a delay whilst held.
	///</summary>
	__LIB Event<void(Window*, KeyDownArgs&)>& OnKeyDown( );

	///<summary>
	///	Called when a key is released from its previously clicked state.
	///</summary>
	__LIB Event<void(Window*, KeyUpArgs&)>& OnKeyUp( );

	///<summary>
	/// Called after KeyDown has been called with the respective character represenation of the key pressed.
	///</summary>
	__LIB Event<void(Window*, KeyDownCharArgs&)>& OnKeyDownChar( );

	///<summary>
	/// Called when the window should paint.
	///</summary>
	__LIB Event<void(Window*, BasePainter*)>& OnPaint( );

	///<summary>
	/// You can use this handle custom messages.
	///</summary>
	__LIB Event<void(Window*, MessageDataArgs&)>& OnHandleMessage( );

	///<summary>
	/// Called every tick.
	///</summary>
	__LIB Event<void(Window*)>& OnTick( );


private:
	using Task = __LIB TimedTask<void(Window*)>;

	Window( );
	__GRAPHICS Window *_parent;
	__GRAPHICS BasePainter *_painter;
	PaintStyle_t _style;
	std::vector<__LIB TimedTask<void(Window*)>*> _tasks;
	HWND _hwnd;
	__MATH Region _region;
	bool _s, _c;

private:
	__LIB Event<void(Window*, WindowMovedArgs&)> _OnWindowMoved;
	__LIB Event<void(Window*, WindowResizeArgs&)> _OnWindowResize;
	__LIB Event<void(Window*)> _OnWindowMaximize, _OnWindowRestored, _OnWindowMinimize, _OnWindowClosed;
	__LIB Event<void(Window*, WindowClosingArgs&)> _OnWindowClosing;
	__LIB Event<void(Window*, MouseMovedArgs&)> _OnMouseMoved;
	__LIB Event<void(Window*, MouseClickedArgs&)> _OnMouseClicked;
	__LIB Event<void(Window*, MouseReleasedArgs&)> _OnMouseReleased;
	__LIB Event<void(Window*, MouseClickedArgs&)> _OnMouseDoubleClicked;
	__LIB Event<void(Window*, ScrollArgs&)> _OnScroll;
	__LIB Event<void(Window*, KeyDownArgs&)> _OnKeyDown;
	__LIB Event<void(Window*, KeyUpArgs&)> _OnKeyUp;
	__LIB Event<void(Window*, KeyDownCharArgs&)> _OnKeyDownChar;
	__LIB Event<void(Window*, BasePainter*)> _OnPaint;
	__LIB Event<void(Window*, MessageDataArgs&)> _OnHandleMessage;
	__LIB Event<void(Window*)> _OnTick;

private:
	__LIB AsyncKeeper _ak_tasks;
	void push_task( Task *_Task );
	void remove_task( std::vector<Task*>::iterator _Where );
};




end_GRAPHICS