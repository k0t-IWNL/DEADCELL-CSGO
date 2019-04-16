#pragma once

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

private:
	LPDIRECT3DDEVICE9 m_device;
	IDirect3DStateBlock9 *m_state_block;

	size_t m_display_size;

public:
	explicit c_dx_renderer( LPDIRECT3DDEVICE9 device );
	~c_dx_renderer( );

	void begin( );
	void end( );

	void pre_d3d_reset( );
	void post_d3d_reset( );

	size_t get_viewport_size( ) const;
	void set_viewport( const D3DVIEWPORT9 &viewport );

	void set_display_size( size_t &size );
	size_t get_display_size( ) const;
};
