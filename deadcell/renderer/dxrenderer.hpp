#pragma once

#include "../color/color.hpp"

#define COL2DWORD( x ) ( D3DCOLOR_ARGB( x.alpha, x.red, x.green, x.blue ) )

class c_dx_renderer {
	// util
	class size_t {
	private:
	public:
		int w = 0, h = 0;

		size_t( int width, int height ) : w( width ), h( height ) {

		}
	};

	class position_t {
	private:
	public:
		int x = 0, y = 0;

		position_t( int x_pos, int y_pos ) : x( x_pos ), y( y_pos ) {
			
		}
	};

	struct vertex_t {
		float x, y, z, rhw;
		DWORD color;
	};

private:
	LPDIRECT3DDEVICE9 m_device = nullptr;
	IDirect3DStateBlock9 *m_state_block = nullptr;

	size_t m_display_size = { 0, 0 };

public:

	void init( IDirect3DDevice9 *device );
	void release( );

	void begin( );
	void end( );

	void pre_d3d_reset( );
	void post_d3d_reset( );

	size_t get_viewport_size( ) const;
	void set_viewport( const D3DVIEWPORT9 &viewport );

	size_t get_display_size( ) const;
	void set_display_size( size_t &size );

	void filled_rect( int posx1, int posy1, int posx2, int posy2, nigger::Color color ) const;
};

