#pragma once
#include "lib.h"
#include "Vector2.h"

begin_MATH

class Region
{
public:
	::dx::lib::Math::Vector2 position, size;

	///<summary>
	/// Moves the position by '_Amount' amount.
	///</summary>
	Region &MoveBy( const ::dx::lib::Math::Vector2 &_Amount );
	
	///<summary>
	/// Moves the position to '_Position'.
	///</summary>
	Region &MoveTo( const ::dx::lib::Math::Vector2 &_Position );

	///<summary>
	/// Resizes the size by '_Amount' amount.
	///</summary>
	Region &ResizeBy( const ::dx::lib::Math::Vector2 &_Amount );

	///<summary>
	/// Resizes the size to '_Size'.
	///</summary>
	Region &ResizeTo( const ::dx::lib::Math::Vector2 &_Size );

	///</summary>
	/// Returns wether '_Other' positon intersects with this Region.
	///</summary>
	bool Intersects( const ::dx::lib::Math::Region &_Other );
};


end_MATH


