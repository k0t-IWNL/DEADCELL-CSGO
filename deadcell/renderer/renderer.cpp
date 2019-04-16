#include "../inc.hpp"
#include "renderer.hpp"

c_dx_renderer::c_dx_renderer( LPDIRECT3DDEVICE9 device )
	: m_device( device ), m_state_block( nullptr ), m_display_size( get_viewport_size( ) ) {
	
}

c_dx_renderer::~c_dx_renderer( ) {
	if( m_state_block )
		m_state_block->Release( );
}

void c_dx_renderer::begin( ) {
	m_state_block->Capture( );

	m_device->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 );

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

	return { vp.Width, vp.Height };
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

