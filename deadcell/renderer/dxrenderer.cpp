#include "../inc.hpp"
#include "dxrenderer.hpp"

void c_dx_renderer::init( IDirect3DDevice9 *device ) {
	m_device = device;
	m_display_size = get_viewport_size( );
}

void c_dx_renderer::release( ) {
	if( m_state_block )
		m_state_block->Release( );
}

void c_dx_renderer::begin( ) {
	m_device->SetVertexShader( nullptr );
	m_device->SetPixelShader( nullptr );
	
	m_device->SetRenderState( D3DRS_LIGHTING, FALSE );
	m_device->SetRenderState( D3DRS_FOGENABLE, FALSE );
	m_device->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
	m_device->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );
	m_device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	m_device->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
	m_device->SetRenderState( D3DRS_SCISSORTESTENABLE, TRUE );
	m_device->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
	m_device->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, FALSE );
	
	m_device->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
	m_device->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );
	
	m_device->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	m_device->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	m_device->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	
	m_device->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	m_device->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
	m_device->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	
	m_device->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	m_device->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	
	m_device->SetTextureStageState( 1, D3DTSS_COLOROP, D3DTOP_DISABLE );
	
	m_device->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	m_device->SetRenderState( D3DRS_SRGBWRITEENABLE, FALSE );
	
	m_device->SetRenderState( D3DRS_SEPARATEALPHABLENDENABLE, TRUE );
	m_device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	m_device->SetRenderState( D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA );
	m_device->SetRenderState( D3DRS_DESTBLENDALPHA, D3DBLEND_ONE );
}

void c_dx_renderer::end( ) {
	if( !m_state_block )
		return;

	m_state_block->Apply( );
}

// invalidate.
void c_dx_renderer::pre_d3d_reset( ) {
	m_state_block->Release( );
}

// restore.
void c_dx_renderer::post_d3d_reset( ) {
	m_device->CreateStateBlock( D3DSBT_PIXELSTATE, &m_state_block );
}

c_dx_renderer::size_t c_dx_renderer::get_viewport_size( ) const {
	D3DVIEWPORT9 vp;
	m_device->GetViewport( &vp );

	return { static_cast< int >( vp.Width ), static_cast< int >( vp.Height ) };
}

void c_dx_renderer::set_viewport( const D3DVIEWPORT9 &viewport ) {
	m_device->SetViewport( &viewport );
}

c_dx_renderer::size_t c_dx_renderer::get_display_size( ) const {
	return m_display_size;
}

void c_dx_renderer::set_display_size( size_t &size ) {
	m_display_size = size;
}

// DRAWING 

void c_dx_renderer::filled_rect( int posx1, int posy1, int posx2, int posy2, nigger::Color color ) const {
	D3DCOLOR d3d_color = COL2DWORD( color );

	vertex_t vert[ 4 ] = {
		{ float( posx1 ), float( posy1 ), 0.f, 1.f, d3d_color },
		{ float( posx2 ), float( posy1 ), 0.f, 1.f, d3d_color },
		{ float( posx1 ), float( posy2 ), 0.f, 1.f, d3d_color },
		{ float( posx2 ), float( posy2 ), 0.f, 1.f, d3d_color }
	};

	m_device->SetTexture( 0, nullptr );
	m_device->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, &vert, sizeof( vertex_t ) );
}
