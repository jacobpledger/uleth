/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "simp.h"
#define foo 127
#define Pi 3.1415926

bool_t
xdr_operands(XDR *xdrs, operands *objp)
{

	if (!xdr_int(xdrs, &objp->x))
		return (FALSE);
	if (!xdr_int(xdrs, &objp->y))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_result(XDR *xdrs, result *objp)
{

	if (!xdr_int(xdrs, &objp->x))
		return (FALSE);
	if (!xdr_int(xdrs, &objp->y))
		return (FALSE);
	if (!xdr_int(xdrs, &objp->r))
		return (FALSE);
	return (TRUE);
}