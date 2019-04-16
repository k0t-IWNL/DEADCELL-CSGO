#include "../../inc.hpp"
#include "../../features/visuals/visuals.h"
#include "../../features/nade_pred/nade_pred.h"
#include "../../features/anti-aim/antiaim.h"

c_dx_renderer dx{ };

HRESULT __stdcall hook::Present( IDirect3DDevice9Ex *device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion ) {
	static bool once { false };
	if ( !once ) {
		/*
		g_renderer.init( device );
		g_menu.init( );
		g_input.init( "Valve001", g_renderer.get_instance( ) );
		*/

		dx.init( device );
		once = true;
	}

	dx.begin( );

	dx.filled_rect( 25, 25, 500, 500, nigger::Color( 255, 255, 255, 255 ) );

	dx.end( );

	return g_hooks.m_directx.get_old_method< fn::Present_t >( hook::idx::PRESENT )( device, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion );
}
