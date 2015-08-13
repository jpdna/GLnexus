#ifndef GLNEXUS_ALLELES_H
#define GLNEXUS_ALLELES_H

#include "types.h"

namespace GLnexus {

// unification_config...

/// Compute unified sites from all discovered alleles in some genomic region
Status unified_sites(const discovered_alleles& alleles, std::vector<unified_site>& ans);

}

#endif