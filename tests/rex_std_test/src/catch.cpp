// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: catch.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

// NOLINTBEGIN

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_DISABLE_EXCEPTIONS
#include "rex_std_test/catch2/catch.hpp"

#define RSL_CATCH_REGISTER_REPORTER(name, reporterType)                                                                                                                                                                                                \
        CATCH_INTERNAL_START_WARNINGS_SUPPRESSION                                                                                                                                                                                                        \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS                                                                                                                                                                                                         \
        namespace                                                                                                                                                                                                                                        \
        {                                                                                                                                                                                                                                                \
          Catch::ReporterRegistrar<Catch:: reporterType> catch_internal_RegistrarFor##reporterType(name);                                                                                                                                                        \
        }                                                                                                                                                                                                                                                \
        CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION

RSL_CATCH_REGISTER_REPORTER("console", ConsoleReporter)

// NOLINTEND
