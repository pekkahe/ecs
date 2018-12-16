assert_is_set(EXT_DIR)

add_library(GLM INTERFACE)

set(GLM_DIR "${EXT_DIR}/glm")
set(GLM_INCLUDE "${GLM_DIR}")

target_include_directories(GLM INTERFACE ${GLM_INCLUDE})