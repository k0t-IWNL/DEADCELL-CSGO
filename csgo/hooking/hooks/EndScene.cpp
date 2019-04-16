#include "../../inc.hpp"
#include "../../features/visuals/visuals.h"
#include "../../features/nade_pred/nade_pred.h"

IDirect3DVertexDeclaration9* vert_dec; 
IDirect3DVertexShader9* vert_shader;
DWORD old_colorwrite;

void save( IDirect3DDevice9Ex* device ) {
	device->GetRenderState( D3DRS_COLORWRITEENABLE, &old_colorwrite );
	device->GetVertexDeclaration( &vert_dec );
	device->GetVertexShader( &vert_shader );
	device->SetRenderState( D3DRS_COLORWRITEENABLE, 0xffffffff );
	device->SetRenderState( D3DRS_SRGBWRITEENABLE, false );
	device->SetSamplerState( NULL, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
	device->SetSamplerState( NULL, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );
	device->SetSamplerState( NULL, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP );
	device->SetSamplerState( NULL, D3DSAMP_SRGBTEXTURE, NULL );
}

void restore( IDirect3DDevice9Ex *device ) {
	device->SetRenderState( D3DRS_COLORWRITEENABLE, old_colorwrite );
	device->SetRenderState( D3DRS_SRGBWRITEENABLE, true );
	device->SetVertexDeclaration( vert_dec );
	device->SetVertexShader( vert_shader );
}



long __stdcall hook::EndScene( IDirect3DDevice9Ex *device ) {
	

	return g_hooks.m_directx.get_old_method< fn::EndScene_t >( hook::idx::END_SCENE )( device );
}
