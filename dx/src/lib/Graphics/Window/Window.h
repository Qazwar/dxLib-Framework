#pragma once
#include "../lib.h"
#include "../../../dx.h"
#include "../../Math/Region.h"
#include "../../event.h"

begin_GRAPHICS



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
};


class KeyUpArgs : public EventArgs
{
public:
	__DX uint key_code;
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
};

class MouseClickedArgs : public EventArgs
{
public:
	__DX uint key;
	__MATH Vector2 position;
};

class MouseReleasedArgs : public EventArgs
{
public:
	__DX uint key;
	__MATH Vector2 position;
};



class Window
{
public:

	static Window* Create( const __LIB String &_Class, 
						   const __LIB String &_Title,
						   const __MATH Region &_Region,
						   DWORD dwStyle = WS_OVERLAPPEDWINDOW,
						   DWORD dwExStyle = 0L );


public:
	~Window( );

public:
		// Wrappers
	bool ClientToScreen( __MATH Vector2 &_PointOut );
	bool ScreenToClient( __MATH Vector2 &_PointOut );
	__LIB String getTitle( );
	void setTitle( const __LIB String &_Title );
	__LIB String getClass( );
	bool HideWindow( );
	bool ShowWindow( );
	bool BringToTop( );
	bool UpdateWindow( );

	HWND native_handle( );
	void Close( );
	LRESULT HandleInput( HWND hWnd, __DX uint Msg, WPARAM wParam, LPARAM lParam );
	bool PollEvents( );
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


private:
	Window( );
	HWND _hwnd;
	__MATH Region _region;
	__LIB Event<void(Window*, WindowMovedArgs&)> _OnWindowMoved;
	__LIB Event<void(Window*, WindowResizeArgs&)> _OnWindowResize;
	__LIB Event<void(Window*)> _OnWindowMaximize, _OnWindowRestored, _OnWindowMinimize, _OnWindowClosed;
	__LIB Event<void(Window*, WindowClosingArgs&)> _OnWindowClosing;
	__LIB Event<void(Window*, MouseMovedArgs&)> _OnMouseMoved;
	__LIB Event<void(Window*, MouseClickedArgs&)> _OnMouseClicked;
	__LIB Event<void(Window*, MouseReleasedArgs&)> _OnMouseReleased;
	__LIB Event<void(Window*, MouseClickedArgs&)> _OnMouseDoubleClicked;
	__LIB Event<void(Window*, KeyDownArgs&)> _OnKeyDown;
	__LIB Event<void(Window*, KeyUpArgs&)> _OnKeyUp;
	__LIB Event<void(Window*, KeyDownCharArgs&)> _OnKeyDownChar;
};




end_GRAPHICS