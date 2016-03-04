
#include <legato.h>

#define RELAY_NB 8

static bool RelayStates[RELAY_NB] = {0};

//--------------------------------------------------------------------------------------------------
/**
 * Returns the total number of relays controlled by the system.
 */
//--------------------------------------------------------------------------------------------------
le_result_t relayControl_Count(uint8_t *countPtr)
{
    *countPtr = RELAY_NB;
    return LE_OK;
}

//--------------------------------------------------------------------------------------------------
/**
 * Get the state of a relay.
 */
//--------------------------------------------------------------------------------------------------
le_result_t relayControl_GetState(uint8_t id, bool *statePtr)
{
    if(id >= RELAY_NB)
    {
        LE_ERROR("Relay id %u not controlled.", id);
        return LE_OUT_OF_RANGE;
    }

    *statePtr = RelayStates[id];
    return LE_OK;
}

//--------------------------------------------------------------------------------------------------
/**
 * Set the state of a relay.
 */
//--------------------------------------------------------------------------------------------------
le_result_t relayControl_SetState(uint8_t id, bool statePtr)
{
    if(id >= RELAY_NB)
    {
        LE_ERROR("Relay id %u not controlled.", id);
        return LE_OUT_OF_RANGE;
    }

    RelayStates[id] = statePtr;
    return LE_OK;
}

//--------------------------------------------------------------------------------------------------
/**
 * Initialization function for the relay component
 */
//--------------------------------------------------------------------------------------------------
COMPONENT_INIT
{
}
