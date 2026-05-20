import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

# Definiert den Namespace deiner C++ Klasse
custom_touch_ns = cg.esphome_ns.namespace('custom_touch')
CustomTouch = custom_touch_ns.class_('CustomTouch', cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(CustomTouch),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
