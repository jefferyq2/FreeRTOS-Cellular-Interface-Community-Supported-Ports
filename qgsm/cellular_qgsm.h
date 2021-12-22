#ifndef __CELLULAR_QGSM_H__
#define __CELLULAR_QGSM_H__

/* AT Command timeout for PDN activation */
#define PDN_ACTIVATION_PACKET_REQ_TIMEOUT_MS       ( 150000UL )

/* AT Command timeout for PDN deactivation. */
#define PDN_DEACTIVATION_PACKET_REQ_TIMEOUT_MS     ( 40000UL )

/* AT Command timeout for Socket connection */
#define SOCKET_CONNECT_PACKET_REQ_TIMEOUT_MS       ( 150000UL )

#define PACKET_REQ_TIMEOUT_MS                      ( 5000UL )

/* AT Command timeout for Socket disconnection */
#define SOCKET_DISCONNECT_PACKET_REQ_TIMEOUT_MS    ( 20000UL )

#define DATA_SEND_TIMEOUT_MS                       ( 50000UL )
#define DATA_READ_TIMEOUT_MS                       ( 50000UL )

/**
 * @brief DNS query result.
 */
typedef enum cellularDnsQueryResult
{
    CELLULAR_DNS_QUERY_SUCCESS,
    CELLULAR_DNS_QUERY_FAILED,
    CELLULAR_DNS_QUERY_MAX,
    CELLULAR_DNS_QUERY_UNKNOWN
} cellularDnsQueryResult_t;

typedef struct cellularModuleContext cellularModuleContext_t;

/**
 * @brief DNS query URC callback fucntion.
 */
typedef void ( * CellularDnsResultEventCallback_t )( cellularModuleContext_t * pModuleContext,
                                                     char * pDnsResult,
                                                     char * pDnsUsrData );

typedef struct cellularModuleContext
{
    /* DNS related variables. */
    PlatformMutex_t dnsQueryMutex; /* DNS query mutex to protect the following data. */
    QueueHandle_t pktDnsQueue;     /* DNS queue to receive the DNS query result. */
    uint8_t dnsResultNumber;       /* DNS query result number. */
    uint8_t dnsIndex;              /* DNS query current index. */
    char * pDnsUsrData;            /* DNS user data to store the result. */
    CellularDnsResultEventCallback_t dnsEventCallback;
    /* Forward declaration to declar the callback function prototype. */
    /* coverity[misra_c_2012_rule_1_1_violation]. */
} cellularModuleContext_t;

CellularPktStatus_t _Cellular_ParseSimstat( char * pInputStr,
                                            CellularSimCardState_t * pSimState );

void _Cellular_ProcessSocketOpen( CellularContext_t * pContext,
                                  char * pInputLine );
/**
 *
 * @brief Cellular module TCPIP enable function.
 *
 * This function start the TCPIP task.
 *
 * @param[in,out] pContext FreeRTOS Cellular Library context created in Cellular_Init.
 *
 * @return CELLULAR_SUCCESS if the operation is successful, otherwise an error
 * code indicating the cause of the error.
 */
CellularError_t Cellular_StartTCPIP( CellularContext_t * pContext );

#endif /* ifndef __CELLULAR_qgsm_H__ */
