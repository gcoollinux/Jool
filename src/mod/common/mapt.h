#ifndef SRC_MOD_COMMON_MAPT_H_
#define SRC_MOD_COMMON_MAPT_H_

#include "mod/common/translation_state.h"

int mapt_init(
		struct mapt_globals *cfg,
		struct ipv6_prefix *euip,
		struct mapping_rule *bmr,
		unsigned int a,
		unsigned int k
);

verdict translate_addrs46_mapt(
		struct xlation *state,
		struct in6_addr *out_src,
		struct in6_addr *out_dst
);

verdict translate_addrs64_mapt(
		struct xlation *state,
		__be32 *out_src,
		__be32 *out_dst
);

#endif /* SRC_MOD_COMMON_MAPT_H_ */