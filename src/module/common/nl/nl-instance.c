#include "nl/nl-instance.h"

#include "xlator.h"
#include "nl/nl-common.h"
#include "nl/nl-core.h"

static int handle_instance_add(struct genl_info *info,
		union request_instance *request)
{
	log_debug("Adding Jool instance.");
	return nlcore_respond(info, xlator_add(NULL, request->add.type,
			request->name));
}

static int handle_instance_rm(struct genl_info *info,
		union request_instance *request)
{
	log_debug("Removing Jool instance.");
	return nlcore_respond(info, xlator_rm(request->name));
}

int handle_instance_request(struct genl_info *info)
{
	struct request_hdr *hdr = get_jool_hdr(info);
	union request_instance *request = (union request_instance *)(hdr + 1);

	if (verify_privileges())
		return nlcore_respond(info, -EPERM);

	switch (be16_to_cpu(hdr->operation)) {
	case OP_ADD:
		return handle_instance_add(info, request);
	case OP_REMOVE:
		return handle_instance_rm(info, request);
	}

	log_err("Unknown operation: %u", be16_to_cpu(hdr->operation));
	return nlcore_respond(info, -EINVAL);
}