#ifndef CPU_WAIFUGENERATOR_CORE_H
#define CPU_WAIFUGENERATOR_CORE_H

#define _WF_BEGIN namespace WaifuCPU {
#define _WF_END }
#define _WF_CALL WaifuCPU::

#define C_ALL(X) cbegin(X), cend(X)

_WF_BEGIN

    const static double C_ETA           = 0.31f; // Learning rate
    const static double C_ALPHA         = 0.9f;  // Momentum
    const static double C_SMOOTH_FACTOR = 100.0f;

_WF_END

#endif // !CPU_WAIFUGENERATOR_NETWORK_CONSTANTS_H
