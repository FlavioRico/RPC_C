/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _REQUESTS_H_RPCGEN
#define _REQUESTS_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct Posicion {
	int x;
	int y;
};
typedef struct Posicion Posicion;

struct InfoAuto {
	Posicion posicion_pasajero;
	char *tipo;
	char *placa;
	int status;
};
typedef struct InfoAuto InfoAuto;

struct Data {
	Posicion posicion_final;
	char *placa;
};
typedef struct Data Data;

#define REQUESTS 0x20000199
#define SOLICITARVIAJEVERS1 1

#if defined(__STDC__) || defined(__cplusplus)
#define SOLICITARVIAJE 1
extern  InfoAuto * solicitarviaje_1(Posicion *, CLIENT *);
extern  InfoAuto * solicitarviaje_1_svc(Posicion *, struct svc_req *);
#define TERMINARVIAJE 2
extern  void * terminarviaje_1(Data *, CLIENT *);
extern  void * terminarviaje_1_svc(Data *, struct svc_req *);
extern int requests_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define SOLICITARVIAJE 1
extern  InfoAuto * solicitarviaje_1();
extern  InfoAuto * solicitarviaje_1_svc();
#define TERMINARVIAJE 2
extern  void * terminarviaje_1();
extern  void * terminarviaje_1_svc();
extern int requests_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_Posicion (XDR *, Posicion*);
extern  bool_t xdr_InfoAuto (XDR *, InfoAuto*);
extern  bool_t xdr_Data (XDR *, Data*);

#else /* K&R C */
extern bool_t xdr_Posicion ();
extern bool_t xdr_InfoAuto ();
extern bool_t xdr_Data ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_REQUESTS_H_RPCGEN */
