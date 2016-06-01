#@format=datatools::configuration::variant
#@format.version=1.0
#@organization=snemo
#@application=falaise

[registry="geometry"]
layout = "Basic"
layout/if_basic/magnetic_field = true
layout/if_basic/magnetic_field/is_active/type = "UniformVertical"
layout/if_basic/magnetic_field/is_active/type/if_uniform_vertical/direction = "+z"
layout/if_basic/magnetic_field/is_active/type/if_uniform_vertical/magnitude = 25 gauss
layout/if_basic/source_calibration = false
layout/if_basic/source_layout = "Basic"
layout/if_basic/source_layout/if_basic/material = "Se82"
layout/if_basic/source_layout/if_basic/thickness = 250 um

[registry="simulation"]
physics_mode = "Constructors"
physics_mode/if_constructors/em_model = "livermore"
production_cuts = true
