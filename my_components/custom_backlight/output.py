
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output
from esphome.const import CONF_ID

# Definition der Namensräume
custom_backlight_ns = cg.esphome_ns.namespace("custom_backlight")
CustomBacklightOutput = custom_backlight_ns.class_(
    "CustomBacklightOutput", output.BinaryOutput, cg.Component
)

CONFIG_SCHEMA = output.BINARY_OUTPUT_SCHEMA.extend(
    {
        cv.Required(CONF_ID): cv.declare_id(CustomBacklightOutput),
    }
).extend(cv.COMPONENT_SCHEMA)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield output.register_output(var, config)
