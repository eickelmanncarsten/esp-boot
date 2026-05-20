import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output
from esphome.const import CONF_ID

# Namespace definieren (muss exakt zum C++ Code passen)
custom_backlight_ns = cg.esphome_ns.namespace('custom_backlight')
CustomBacklightOutput = custom_backlight_ns.class_('CustomBacklightOutput', output.BinaryOutput, cg.Component)

CONF_PCA9554_ID = "pca9554_id"

CONFIG_SCHEMA = output.BINARY_OUTPUT_SCHEMA.extend({
    cv.Required(CONF_ID): cv.declare_id(CustomBacklightOutput),
    cv.Required(CONF_PCA9554_ID): cv.use_id(cg.Component),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await output.register_output(var, config)
    
    hub = await cg.get_variable(config[CONF_PCA9554_ID])
    cg.add(var.set_pin_hub(hub))
