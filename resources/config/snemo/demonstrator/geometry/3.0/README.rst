================================
SuperNEMO virtual geometry setup
================================

:Authors: François Mauger, Xavier Garrido
:Date:    2013-10-30

.. contents::
   :depth: 3
..

Presentation
============

This directory contains  the files needed to describe  the geometry of
the full SuperNEMO demonstrator module.

 * Setup label is : ``snemo::demonstrator``
 * Setup version is : ``3.0``


Files:

 * ``README.rst`` : this file,
 * ``manager.conf``   :   the   main   configuration   file   of   the
   Bayeux/geomtools geometry manager object,
 * ``categories.lis``  : the  description of  all geometry  categories
   associated to physical  volumes of interest in  the geometry setup;
   this  allows to  build  a  dictionnary of  geometry  IDs to  enable
   automated location  of volumes  and navigation within  the geometry
   model,
 * Files  dedicated   to  the  building  of   *geometry  models*  (ala
   Geant4/GDML logical volume factories):

   * ``setup.geom`` :
   * ``module_0.geom`` :
   * ``calorimeter_modules/calorimeter_module.geom`` :
   * ``calorimeter_modules/calorimeter_submodules.geom``:
   * ``calorimeter_modules/calorimeter_walls.geom``:
   * ``calorimeter_modules/pmt_8inch.geom``:
   * ``tracker_modules/gveto.geom``:
   * ``tracker_modules/gveto_module.geom``:
   * ``tracker_modules/pmt_5inch.geom``:
   * ``tracker_modules/tracker_drift_cell_base.geom``:
   * ``tracker_modules/tracker_drift_cell_nodes.geom``:
   * ``tracker_modules/tracker_layers.geom``:
   * ``tracker_modules/tracker_submodules.geom``:
   * ``tracker_modules/tracker_volumes.geom``:
   * ``tracker_modules/xwall.geom``:
   * ``tracker_modules/xwall_module.geom``:
   * ``source_module/source_calibration.geom``:
   * ``source_module/source_foil_support.geom``:
   * ``source_module/source_frame_horizontal_beams.geom``:
   * ``source_module/source_frame_vertical_beams.geom``:
   * ``source_module/source_module.geom``:
   * ``source_module/source_strips.geom``:


Check the geometry:

  The  SuperNEMO  demonstrator virtual  geometry  relies  not only  on
  generic geometry  model classes implemented in  Bayeux/geomtools but
  also on dedicated geometry model classes from the Falaise_sngeometry
  library.  It is  thus needed to build this library  in order to load
  and visualize the SuperNEMO virtual geometry setup.

  1. First make sure the Bayeux software is installed and setup: ::

      $ which bxgeomtools_inspector

  2. Build Falaise from a build directory of your choice.
  3. Then from Falaise build directory, run: ::
      $ LD_LIBRARY_PATH="$(pwd)/BuildProducts/lib:${LD_LIBRARY_PATH}" \
        bxgeomtools_inspector \
          --datatools::logging "warning" \
          --datatools::resource_path "falaise@$(pwd)/BuildProducts/share/Falaise-1.0.0/resources" \
          --load-dll Falaise \
          --manager-config "@falaise:config/snemo/demonstrator/geometry/3.0/manager.conf"

     where:

       * ``--datatools::resource_path "falaise@$(pwd)/resources"``
         registers  the   Falaise  resource  base  directory   in  the
         datatools' kernel for automated search for configuration file
         paths,
       * ``--manager-config
         "@falaise:config/snemo/demonstrator/geometry/3.0/manager.conf"``
         indicates the main configuration file of the geometry manager.
