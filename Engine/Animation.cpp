#include "Animation.h"
#include "SpriteEffect.h"

Animation::Animation( int x,int y,int width,int height,int count,
	const Surface& sheet,float holdTime,Color chroma )
	:
	sprite( sheet ),
	holdTime( holdTime ),
	chroma( chroma )
{
	for( int i = 0; i < count; ++i )
	{
		frames.emplace_back( x + i * width,
			x + ( i + 1 ) * width,y,y + height );
	}
}

void Animation::Update( float dt )
{
	curFrameTime += dt;
	while( curFrameTime >= holdTime )
	{
		Advance();
		curFrameTime -= holdTime;
	}
}

void Animation::Draw( const Vec2& pos,Graphics& gfx ) const
{
	gfx.DrawSprite( int( pos.x ),int( pos.y ),
		frames[iCurFrame],sprite,
		SpriteEffect::Chroma{ chroma } );
}

void Animation::Draw( const Vec2& pos,Graphics& gfx,const RectI& clip ) const
{
	gfx.DrawSprite( int( pos.x ),int( pos.y ),
		frames[iCurFrame],clip,sprite,
		SpriteEffect::Chroma{ chroma } );
}

void Animation::Advance()
{
	if( ++iCurFrame >= frames.size() )
	{
		iCurFrame = 0;
	}
}
