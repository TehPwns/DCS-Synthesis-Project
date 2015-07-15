#include "resource_binding.h"

namespace binding
{

vvint registerBind(const graph& resource_conflict)
{
    (void)resource_conflict;
    vvint result;

    return result;
}

vvint functionalBind(const graph& function_conflict, const std::string& type)
{
    vvint result;
    (void)function_conflict;
    (void)type;

    return result;
}

}
