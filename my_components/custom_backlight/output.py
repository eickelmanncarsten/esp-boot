import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output
from esphome.const import CONF_ID

# Definition der Namensräume
custom_backlight_ns = cg.esphome_ns.namespace("custom_backlight")
CustomBacklightOutput = custom_backlight_ns.class_(
    "CustomBacklightOutput", output.BinaryOutput, cg.Component
)

# Wir fügen die optionale Übergabe der Hub-ID im Schema hinzu
CONFIG_SCHEMA = output.BINARY_OUTPUT_SCHEMA.extend(
    {
        cv.Required(CONF_ID): cv.declare_id(CustomBacklightOutput),
        cv.Optional("pca9554_id"): cv.use_id(cg.Component),
    }
).extend(cv.COMPONENT_SCHEMA)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield output.register_output(var, config)
    
    # KORREKTUR: Übergabe des Expanders an C++
    if "pca9554_id" in config:
        hub = yield cg.get_variable(config["pca9554_id"])
        cg.add(var.set_pin_hub(hub))
