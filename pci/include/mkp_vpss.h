#ifndef  __MPI_VPSS_H__
#define  __MPI_VPSS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

#include "hi_math.h"
#include "hi_common.h"
#include "hi_comm_vpss.h"
#include "hi_inner_fisheye.h"
#include "mkp_ioctl.h"


#define VPSS_MAKE_IOCFD(grp,chn)    ((((grp) & 0xff) << 16) | ((chn) & 0xff))
#define VPSS_GETGRP_BY_IOCFD(f)    (((f) >> 16) & 0xff)
#define VPSS_GETCHN_BY_IOCFD(f)     ((f) & 0xff)

#define VPSS_TRACE(level, fmt...)\
do{ \
        HI_TRACE(level, HI_ID_VPSS,"[Func]:%s [Line]:%d [Info]:", __FUNCTION__, __LINE__);\
        HI_TRACE(level,HI_ID_VPSS,##fmt);\
}while(0)
        
typedef struct HI_VPSS_ZOOM_FACTOR_S
{
    HI_S32 HZoomOutFactor;
    HI_S32 VZoomOutFactor;
    HI_U32 HZoomInFactor;
    HI_U32 VZoomInFactor;
}VPSS_ZOOM_FACTOR_S;

typedef enum hiVPSS_PRESCALE_E
{
	VPSS_PRESCALE_NULL = 0,
	VPSS_PRESCALE_TDE,
    VPSS_PRESCALE_VPSS,                     
} VPSS_PRESCALE_E;

typedef struct hiVPSS_USR_GET_FRM_TIMEOUT_S
{
    VIDEO_FRAME_INFO_S *pstVFrame;
    HI_S32              s32MilliSec;
} VPSS_USR_GET_FRM_TIMEOUT_S;

typedef struct hiVPSS_FISHEYE_LDC_ATTR_S
{
    VPSS_LDC_ATTR_S		    stLDCAttr;
	FISHEYE_FIRMWARE_ATTR_S	stFisheyeFirmAttr;
}VPSS_FISHEYE_LDC_ATTR_S;


typedef struct hiVPSS_FISHEYE_ROTATEEX_ATTR_S
{
    VPSS_ROTATE_EX_ATTR_S   stRotateExAttr;
    HI_S32                  asPMF[FISHEYE_PMFCOEF_NUM];
    FISHEYE_FIRMWARE_ATTR_S stFisheyeFirmAttr;
}VPSS_FISHEYE_ROTATEEX_ATTR_S;


typedef struct hiVPSS_PMF_ATTR_S
{
	HI_BOOL     				bEnable;	
	HI_S32      				as32PMFCoef[FISHEYE_PMFCOEF_NUM];
	SIZE_S      				stDestSize;
}VPSS_PMF_ATTR_S;

typedef struct hiVPSS_FISHEYE_SPREAD_ATTR_S
{
	SPREAD_ATTR_S 			stSpreadAttr;
    VPSS_PMF_ATTR_S			stVpssPmfAttr;
	FISHEYE_FIRMWARE_ATTR_S	stFisheyeFirmAttr;
} VPSS_FISHEYE_SPREAD_ATTR_S;

/*-------------------------------------------------------------------------*/

typedef enum hiIOC_NR_VPSS_E
{   
    IOC_NR_VPSS_GRP_ATTR_SET = 0,
    IOC_NR_VPSS_GRP_ATTR_GET,
    
    IOC_NR_VPSS_GRP_START,
    IOC_NR_VPSS_GRP_STOP,

    IOC_NR_VPSS_GRP_RESET,

    IOC_NR_VPSS_CHN_ATTR_SET,
    IOC_NR_VPSS_CHN_ATTR_GET,

    IOC_NR_VPSS_CHN_ENABLE,
    IOC_NR_VPSS_CHN_DISABLE,

    IOC_NR_VPSS_BACKUP_ENABLE,
    IOC_NR_VPSS_BACKUP_DISABLE,

    IOC_NR_VPSS_GRP_CREATE,
    IOC_NR_VPSS_GRP_DESTROY,

    IOC_NR_VPSS_CROP_CFG_SET,
    IOC_NR_VPSS_CROP_CFG_GET,

    IOC_NR_VPSS_SET_GRP_PARAM,
    IOC_NR_VPSS_GET_GRP_PARAM,

    IOC_NR_VPSS_SET_GRP_NRB_PARAM,
    IOC_NR_VPSS_GET_GRP_NRB_PARAM,

    IOC_NR_VPSS_SET_GRP_NRS_PARAM,
    IOC_NR_VPSS_GET_GRP_NRS_PARAM,

	IOC_NR_VPSS_SET_GRP_NR_PARAM,
    IOC_NR_VPSS_GET_GRP_NR_PARAM,
    
    IOC_NR_VPSS_SET_CHN_PARAM,
    IOC_NR_VPSS_GET_CHN_PARAM,

    IOC_NR_VPSS_SET_MODE,
    IOC_NR_VPSS_GET_MODE,   
    
    IOC_NR_VPSS_SET_DEPTH,
    IOC_NR_VPSS_GET_DEPTH,

    IOC_NR_VPSS_USER_SENDFRAME,
    
    IOC_NR_VPSS_USER_GETFRAME,
    IOC_NR_VPSS_USER_RELEASEFRAME,

    IOC_NR_VPSS_USER_GETGROUPFRAME,
    IOC_NR_VPSS_USER_RELEASEGROUPFRAME,    
    
    IOC_NR_VPSS_GRP_SET_FRAMERATE,
    IOC_NR_VPSS_GRP_GET_FRAMERATE,

    IOC_NR_VPSS_SET_EXTCHN_ATTR,
    IOC_NR_VPSS_GET_EXTCHN_ATTR,

    IOC_NR_VPSS_GRP_SET_DELAY,
    IOC_NR_VPSS_GRP_GET_DELAY,

    IOC_NR_VPSS_SET_CHN_OVERLAY,
    IOC_NR_VPSS_GET_CHN_OVERLAY,

    IOC_NR_VPSS_BIND_FLAG2FD,

    IOC_NR_VPSS_GET_REGION_LUMA,

    IOC_NR_VPSS_SET_IMG_QUALITY,
    IOC_NR_VPSS_GET_IMG_QUALITY,

	IOC_NR_VPSS_SET_IMG_QUALITY_NEW,
    IOC_NR_VPSS_GET_IMG_QUALITY_NEW,

    IOC_NR_VPSS_SET_CHN_CROP,
    IOC_NR_VPSS_GET_CHN_CROP,

    IOC_NR_VPSS_SET_CHN_COVER,
    IOC_NR_VPSS_GET_CHN_COVER,
    
    IOC_NR_VPSS_SET_LOW_DELAY_ATTR,
    IOC_NR_VPSS_GET_LOW_DELAY_ATTR, 
    
    IOC_NR_VPSS_CHN_ROTATE_SET,
    IOC_NR_VPSS_CHN_ROTATE_GET,
    
    IOC_NR_VPSS_CHN_LDC_ATTR_SET,
    IOC_NR_VPSS_CHN_LDC_ATTR_GET,
    IOC_NR_VPSS_GET_CHN_OUTPUT_SIZE,
    IOC_NR_VPSS_CHN_FISHEYE_LDC_ATTR_SET,    
	IOC_NR_VPSS_CHN_FISHEYE_LDC_ATTR_GET,
	IOC_NR_VPSS_CHN_FISHEYE_SPREAD_ATTR_SET,    
	IOC_NR_VPSS_CHN_FISHEYE_SPREAD_ATTR_GET,
    IOC_NR_VPSS_CHN_ROTATE_EX_SET,
    IOC_NR_VPSS_CHN_ROTATE_EX_GET,

    IOC_NR_VPSS_SET_EXTCHN_CROP,
    IOC_NR_VPSS_GET_EXTCHN_CROP,

	IOC_NR_VPSS_SET_GRP_FISHEYE_CONFIG,
	IOC_NR_VPSS_GET_GRP_FISHEYE_CONFIG,

	IOC_NR_VPSS_SET_CHN_FISHEYE_ATTR,
	IOC_NR_VPSS_GET_CHN_FISHEYE_ATTR,
	
	IOC_NR_VPSS_SET_STITCH_BLEND_PARAM,
    IOC_NR_VPSS_GET_STITCH_BLEND_PARAM,
	    
	IOC_NR_VPSS_SET_MOD_PARAM,
	IOC_NR_VPSS_GET_MOD_PARAM,
	
    IOC_NR_VPSS_GET_GRP_NRS_AUTO_INFO,
    
    IOC_NR_VPSS_GRP_QUERY,

    IOC_NR_VPSS_SET_GRP_SNAP_NRS_PARAM,
    IOC_NR_VPSS_GET_GRP_SNAP_NRS_PARAM

} IOC_NR_VPSS_E;

#define VPSS_GRP_ATTR_SET_CTRL      _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_GRP_ATTR_SET, VPSS_GRP_ATTR_S)
#define VPSS_GRP_ATTR_GET_CTRL      _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_GRP_ATTR_GET, VPSS_GRP_ATTR_S)

#define VPSS_GRP_START_CTRL         _IO(IOC_TYPE_VPSS, IOC_NR_VPSS_GRP_START)
#define VPSS_GRP_STOP_CTRL          _IO(IOC_TYPE_VPSS,  IOC_NR_VPSS_GRP_STOP)

#define VPSS_GRP_RESET_CTRL         _IO(IOC_TYPE_VPSS,  IOC_NR_VPSS_GRP_RESET)

#define VPSS_CHN_ATTR_SET_CTRL      _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_CHN_ATTR_SET, VPSS_CHN_ATTR_S)
#define VPSS_CHN_ATTR_GET_CTRL      _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_CHN_ATTR_GET, VPSS_CHN_ATTR_S)

#define VPSS_CHN_ENABLE_CTRL        _IO(IOC_TYPE_VPSS, IOC_NR_VPSS_CHN_ENABLE)
#define VPSS_CHN_DISABLE_CTRL       _IO(IOC_TYPE_VPSS, IOC_NR_VPSS_CHN_DISABLE)

#define VPSS_GRP_ENABLE_BACKUP_CTRL        _IO(IOC_TYPE_VPSS, IOC_NR_VPSS_BACKUP_ENABLE)
#define VPSS_GRP_DISABLE_BACKUP_CTRL       _IO(IOC_TYPE_VPSS, IOC_NR_VPSS_BACKUP_DISABLE)

#define VPSS_GRP_CREATE_CTRL        _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_GRP_CREATE,VPSS_GRP_ATTR_S)
#define VPSS_GRP_DESTROY_CTRL       _IO(IOC_TYPE_VPSS, IOC_NR_VPSS_GRP_DESTROY)

#define VPSS_CROP_CFG_SET_CTRL      _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_CROP_CFG_SET,VPSS_CROP_INFO_S)
#define VPSS_CROP_CFG_GET_CTRL      _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_CROP_CFG_GET,VPSS_CROP_INFO_S)

#define VPSS_SET_GRP_PARAM          _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_SET_GRP_PARAM, VPSS_GRP_PARAM_S)
#define VPSS_GET_GRP_PARAM          _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_GET_GRP_PARAM, VPSS_GRP_PARAM_S)

#define VPSS_SET_GRP_NRB_PARAM    _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_SET_GRP_NRB_PARAM, VPSS_GRP_VPPNRB_S)
#define VPSS_GET_GRP_NRB_PARAM    _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_GET_GRP_NRB_PARAM, VPSS_GRP_VPPNRB_S)

#define VPSS_SET_GRP_NRS_PARAM    _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_SET_GRP_NRS_PARAM, VPSS_GRP_NRS_PARAM_S)
#define VPSS_GET_GRP_NRS_PARAM    _IOWR(IOC_TYPE_VPSS, IOC_NR_VPSS_GET_GRP_NRS_PARAM, VPSS_GRP_NRS_PARAM_S)

#define VPSS_SET_GRP_SNAP_NRS_PARAM    _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_SET_GRP_SNAP_NRS_PARAM, VPSS_GRP_SNAP_NRS_PARAM_S)
#define VPSS_GET_GRP_SNAP_NRS_PARAM    _IOWR(IOC_TYPE_VPSS, IOC_NR_VPSS_GET_GRP_SNAP_NRS_PARAM, VPSS_GRP_SNAP_NRS_PARAM_S)

#define VPSS_GET_GRP_NRS_AUTO_INFO    _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_GET_GRP_NRS_AUTO_INFO, VPSS_GRP_NRS_AUTO_INFO_S)

#define VPSS_GRP_QUERY    _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_GRP_QUERY, VPSS_GRP_QUERY_S)

#define VPSS_SET_CHN_PARAM          _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_SET_CHN_PARAM, VPSS_CHN_PARAM_S)
#define VPSS_GET_CHN_PARAM          _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_GET_CHN_PARAM, VPSS_CHN_PARAM_S)

#define VPSS_SET_MODE               _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_SET_MODE, VPSS_CHN_MODE_S)
#define VPSS_GET_MODE               _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_GET_MODE, VPSS_CHN_MODE_S)

#define VPSS_SET_DEPTH              _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_SET_DEPTH, HI_U32)
#define VPSS_GET_DEPTH              _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_GET_DEPTH, HI_U32)

#define VPSS_USER_SENDFRAME      _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_USER_SENDFRAME, VPSS_FRAME_TIMEOUT_S)

#define VPSS_USER_GETFRAME          _IOWR(IOC_TYPE_VPSS, IOC_NR_VPSS_USER_GETFRAME, VPSS_USR_GET_FRM_TIMEOUT_S)
#define VPSS_USER_RELEASEFRAME      _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_USER_RELEASEFRAME, VIDEO_FRAME_INFO_S)

#define VPSS_USER_GETGROUPFRAME      _IOWR(IOC_TYPE_VPSS, IOC_NR_VPSS_USER_GETGROUPFRAME, VPSS_GET_GRP_FRAME_S)
#define VPSS_USER_RELEASEGROUPFRAME  _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_USER_RELEASEGROUPFRAME, VPSS_GET_GRP_FRAME_S)

#define VPSS_SET_FRAMERATE          _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_GRP_SET_FRAMERATE, VPSS_FRAME_RATE_S)
#define VPSS_GET_FRAMERATE          _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_GRP_GET_FRAMERATE, VPSS_FRAME_RATE_S)

#define VPSS_SET_EXTCHN_ATTR        _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_SET_EXTCHN_ATTR, VPSS_EXT_CHN_ATTR_S)       
#define VPSS_GET_EXTCHN_ATTR        _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_GET_EXTCHN_ATTR, VPSS_EXT_CHN_ATTR_S)   

#define VPSS_SET_DELAY              _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_GRP_SET_DELAY, HI_U32)
#define VPSS_GET_DELAY              _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_GRP_GET_DELAY, HI_U32)

#define VPSS_SET_CHN_OVERLAY        _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_SET_CHN_OVERLAY, HI_U32)
#define VPSS_GET_CHN_OVERLAY        _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_GET_CHN_OVERLAY, HI_U32)

#define VPSS_SET_CHN_COVER          _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_SET_CHN_COVER, HI_U32)
#define VPSS_GET_CHN_COVER          _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_GET_CHN_COVER, HI_U32)

#define VPSS_BIND_FLAG2FD           _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_BIND_FLAG2FD, HI_U32)

#define VPSS_GET_REGION_LUMA        _IOWR(IOC_TYPE_VPSS, IOC_NR_VPSS_GET_REGION_LUMA, VPSS_GET_REGION_LUMA_S)

#define VPSS_SET_IMG_QUALITY        _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_SET_IMG_QUALITY, VPSS_IMG_QUALITY_CFG_S)    
#define VPSS_GET_IMG_QUALITY        _IOWR(IOC_TYPE_VPSS, IOC_NR_VPSS_GET_IMG_QUALITY, VPSS_IMG_QUALITY_CFG_S)

#define VPSS_SET_IMG_QUALITY_NEW        _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_SET_IMG_QUALITY_NEW, VPSS_IMG_QUALITY_NEW_CFG_S)    
#define VPSS_GET_IMG_QUALITY_NEW        _IOWR(IOC_TYPE_VPSS, IOC_NR_VPSS_GET_IMG_QUALITY_NEW, VPSS_IMG_QUALITY_NEW_CFG_S)

#define VPSS_SET_CHN_CROP                  _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_SET_CHN_CROP, VPSS_CROP_INFO_S)
#define VPSS_GET_CHN_CROP                  _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_GET_CHN_CROP, VPSS_CROP_INFO_S)

#define VPSS_SET_CHN_LOW_DELAY_ATTR       _IOW(IOC_TYPE_VPSS,IOC_NR_VPSS_SET_LOW_DELAY_ATTR, VPSS_LOW_DELAY_INFO_S)
#define VPSS_GET_CHN_LOW_DELAY_ATTR       _IOR(IOC_TYPE_VPSS,IOC_NR_VPSS_GET_LOW_DELAY_ATTR, VPSS_LOW_DELAY_INFO_S)

#define VPSS_SET_CHN_ROTATE          _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_CHN_ROTATE_SET, HI_U32)
#define VPSS_GET_CHN_ROTATE          _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_CHN_ROTATE_GET, HI_U32)

#define VPSS_SET_CHN_LDC_ATTR        _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_CHN_LDC_ATTR_SET, VPSS_LDC_ATTR_S)
#define VPSS_GET_CHN_LDC_ATTR        _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_CHN_LDC_ATTR_GET, VPSS_LDC_ATTR_S)
#define VPSS_GET_CHN_OUTPUT_SIZE        _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_GET_CHN_OUTPUT_SIZE, SIZE_S)
#define VPSS_CHN_FISHEYE_LDC_SET_CTRL   _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_CHN_FISHEYE_LDC_ATTR_SET, VPSS_FISHEYE_LDC_ATTR_S)
#define VPSS_CHN_FISHEYE_LDC_GET_CTRL   _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_CHN_FISHEYE_LDC_ATTR_GET, VPSS_FISHEYE_LDC_ATTR_S)
#define VPSS_CHN_FISHEYE_SPREAD_SET_CTRL   _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_CHN_FISHEYE_SPREAD_ATTR_SET, VPSS_FISHEYE_SPREAD_ATTR_S)
#define VPSS_CHN_FISHEYE_SPREAD_GET_CTRL   _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_CHN_FISHEYE_SPREAD_ATTR_GET, SPREAD_ATTR_S)

#define VPSS_CHN_ROTATE_EX_SET_CTRL   _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_CHN_ROTATE_EX_SET, VPSS_FISHEYE_ROTATEEX_ATTR_S)
#define VPSS_CHN_ROTATE_EX_GET_CTRL   _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_CHN_ROTATE_EX_GET, VPSS_ROTATE_EX_ATTR_S)

#define VPSS_SET_EXTCHN_CROP        _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_SET_EXTCHN_ATTR, VPSS_CROP_INFO_S)       
#define VPSS_GET_EXTCHN_CROP        _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_GET_EXTCHN_ATTR, VPSS_CROP_INFO_S)   

#define VPSS_SET_GRP_FISHEYE_CONFIG 	_IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_SET_GRP_FISHEYE_CONFIG, FISHEYE_CONFIG_S)
#define VPSS_GET_GRP_FISHEYE_CONFIG 	_IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_GET_GRP_FISHEYE_CONFIG, FISHEYE_CONFIG_S)

#define VPSS_SET_CHN_FISHEYE_ATTR 		_IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_SET_CHN_FISHEYE_ATTR, FISHEYE_DRV_ATTR_S)
#define VPSS_GET_CHN_FISHEYE_ATTR 		_IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_GET_CHN_FISHEYE_ATTR, FISHEYE_ATTR_S)

#define VPSS_SET_STITCH_BLEND_PARAM          _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_SET_STITCH_BLEND_PARAM, VPSS_STITCH_BLEND_PARAM_S)
#define VPSS_GET_STITCH_BLEND_PARAM          _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_GET_STITCH_BLEND_PARAM, VPSS_STITCH_BLEND_PARAM_S)

#define VPSS_SET_MOD_PARAM 		        _IOW(IOC_TYPE_VPSS, IOC_NR_VPSS_SET_MOD_PARAM, VPSS_MOD_PARAM_S)
#define VPSS_GET_MOD_PARAM 		        _IOR(IOC_TYPE_VPSS, IOC_NR_VPSS_GET_MOD_PARAM, VPSS_MOD_PARAM_S)
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif/* End of #ifndef __MPI_PRIV_VPSS_H__*/

