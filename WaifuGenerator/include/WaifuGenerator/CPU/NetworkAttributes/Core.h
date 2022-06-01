// Author: Nikita Kozlov
// Link: github.com/nyarstot
//
// This file is part of WaifuGenerator neural network.
//
// WaifuGenerator is free software: you can redistribute it and/or modify
// it under terms of the GNU Generan Public License as published by
// the free software foundation, either version 3 of License, or
// (at your option) any later version.
//
// WaifuGenerator is distributed in the hope that it will be usefull,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with WaifuGenerator. If not, see <https://www.gnu.org/licenses/>.
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
