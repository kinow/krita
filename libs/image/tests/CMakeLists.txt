# cmake in some versions for some not yet known reasons fails to run automoc
# on random targets (changing target names already has an effect)
# As temporary workaround skipping build of tests on these versions for now
# See https://mail.kde.org/pipermail/kde-buildsystem/2015-June/010819.html
# extend range of affected cmake versions as needed
if(NOT ${CMAKE_VERSION} VERSION_LESS 3.1.3 AND
   NOT ${CMAKE_VERSION} VERSION_GREATER 3.2.3)
    message(WARNING "Skipping krita/image/tests, CMake in at least versions 3.1.3 - 3.2.3 seems to have a problem with automoc.  \n(FRIENDLY REMINDER: PLEASE DON'T BREAK THE TESTS!)")
    set (HAVE_FAILING_CMAKE TRUE)
else()
    set (HAVE_FAILING_CMAKE FALSE)
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/libs/image/metadata
    ${CMAKE_BINARY_DIR}/libs/image/
    ${CMAKE_SOURCE_DIR}/libs/image/
    ${CMAKE_SOURCE_DIR}/libs/image/brushengine
    ${CMAKE_SOURCE_DIR}/libs/image/tiles3
    ${CMAKE_SOURCE_DIR}/libs/image/tiles3/swap
    ${CMAKE_SOURCE_DIR}/sdk/tests
)

include_Directories(SYSTEM
    ${EIGEN3_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
)

if(HAVE_VC)
  include_directories(${Vc_INCLUDE_DIR})
endif()

macro_add_unittest_definitions()

set(KisRandomGeneratorDemoSources kis_random_generator_demo.cpp kimageframe.cpp)
ki18n_wrap_ui(KisRandomGeneratorDemoSources kis_random_generator_demo.ui)
kde4_add_executable(KisRandomGeneratorDemo ${KisRandomGeneratorDemoSources})
target_link_libraries(KisRandomGeneratorDemo  kritaimage )

########### next target ###############

set(kis_base_node_test_SRCS kis_base_node_test.cpp )
kde4_add_unit_test(KisBaseNodeTest TESTNAME krita-image-BaseNodeTest ${kis_base_node_test_SRCS})
target_link_libraries(KisBaseNodeTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_fast_math_test_SRCS kis_fast_math_test.cpp )
kde4_add_unit_test(KisFastMathTest TESTNAME krita-image-FastMathTest ${kis_fast_math_test_SRCS})
target_link_libraries(KisFastMathTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_node_test_SRCS kis_node_test.cpp )
kde4_add_unit_test(KisNodeTest TESTNAME krita-image-Node-Test ${kis_node_test_SRCS})
target_link_libraries(KisNodeTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_node_facade_test_SRCS kis_node_facade_test.cpp )
kde4_add_unit_test(KisNodeFacadeTest TESTNAME krita-image-NodeFacadeTest ${kis_node_facade_test_SRCS})
target_link_libraries(KisNodeFacadeTest   kritaimage Qt5::Test)

########### next target ###############

if (NOT HAVE_FAILING_CMAKE)
  set(kis_paint_device_test_SRCS kis_paint_device_test.cpp )
  kde4_add_broken_unit_test(KisPaintDeviceTest TESTNAME krita-image-KisPaintDeviceTest ${kis_paint_device_test_SRCS})
  target_link_libraries(KisPaintDeviceTest   kritaimage kritaodf Qt5::Test)
else()
  message(WARNING "Skipping KisPaintDeviceTest!!!!!!!!!!!!!!")
endif()

########### next target ###############

set(kis_fixed_paint_device_test_SRCS kis_fixed_paint_device_test.cpp )
kde4_add_unit_test(KisFixedPaintDeviceTest TESTNAME krita-image-KisFixedPaintDeviceTest ${kis_fixed_paint_device_test_SRCS})
target_link_libraries(KisFixedPaintDeviceTest   kritaimage Qt5::Test)


########### next target ###############

set(kis_layer_test_SRCS kis_layer_test.cpp )
kde4_add_unit_test(KisLayerTest TESTNAME krita-image-KisLayerTest  ${kis_layer_test_SRCS})
target_link_libraries(KisLayerTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_effect_mask_test_SRCS kis_effect_mask_test.cpp )
kde4_add_unit_test(KisEffectMaskTest TESTNAME krita-image-KisEffectMaskTest  ${kis_effect_mask_test_SRCS})
target_link_libraries(KisEffectMaskTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_iterator_test_SRCS kis_iterator_test.cpp )
kde4_add_unit_test(KisIteratorTest TESTNAME krita-image-KisIteratorTest  ${kis_iterator_test_SRCS})
target_link_libraries(KisIteratorTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_painter_test_SRCS kis_painter_test.cpp )


kde4_add_unit_test(KisPainterTest TESTNAME krita-image-KisPainterTest ${kis_painter_test_SRCS})

target_link_libraries(KisPainterTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_selection_test_SRCS kis_selection_test.cpp )

kde4_add_unit_test(KisSelectionTest TESTNAME krita-image-SelectionTest ${kis_selection_test_SRCS})

target_link_libraries(KisSelectionTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_count_visitor_test_SRCS kis_count_visitor_test.cpp )

kde4_add_unit_test(KisCountVisitorTest TESTNAME krita-image-KisCountVisitorTest ${kis_count_visitor_test_SRCS})

target_link_libraries(KisCountVisitorTest   kritaimage Qt5::Test)

########### next target ###############
set(kis_projection_test_SRCS kis_projection_test.cpp )

kde4_add_unit_test(KisProjectionTest TESTNAME krita-image-KisProjectionTest ${kis_projection_test_SRCS})

target_link_libraries(KisProjectionTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_properties_configuration_test_SRCS kis_properties_configuration_test.cpp )

kde4_add_unit_test(Kis_Properties_Configuration_Test TESTNAME krita-image-properties-configuration-Test ${kis_properties_configuration_test_SRCS})

target_link_libraries(Kis_Properties_Configuration_Test   kritaimage Qt5::Test)

########### next target ###############

set(kis_transaction_test_SRCS kis_transaction_test.cpp )

kde4_add_unit_test(KisTransactionTest TESTNAME krita-image-KisTransactionTest ${kis_transaction_test_SRCS})

target_link_libraries(KisTransactionTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_pixel_selection_test_SRCS kis_pixel_selection_test.cpp )

kde4_add_unit_test(KisPixelSelectionTest TESTNAME krita-image-KisPixelSelectionTest ${kis_pixel_selection_test_SRCS})

target_link_libraries(KisPixelSelectionTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_group_layer_test_SRCS kis_group_layer_test.cpp )

kde4_add_unit_test(KisGroupLayerTest TESTNAME krita-image-KisGroupLayerTest ${kis_group_layer_test_SRCS})

target_link_libraries(KisGroupLayerTest   kritaimage Qt5::Test)

########### next target ###############

if (NOT HAVE_FAILING_CMAKE)
  set(kis_filter_mask_test_SRCS kis_filter_mask_test.cpp )
  kde4_add_broken_unit_test(KisFilterMaskTest TESTNAME krita-image-KisFilterMaskTest ${kis_filter_mask_test_SRCS})
  target_link_libraries(KisFilterMaskTest   kritaimage Qt5::Test)
else()
  message(WARNING "Skipping KisFilterMaskTest!!!!!!!!!!!!!!")
endif()

########### next target ###############

set(kis_transform_mask_test_SRCS kis_transform_mask_test.cpp )

kde4_add_broken_unit_test(KisTransformMaskTest TESTNAME krita-image-KisTransformMaskTest ${kis_transform_mask_test_SRCS})

target_link_libraries(KisTransformMaskTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_paint_layer_test_SRCS kis_paint_layer_test.cpp )

kde4_add_unit_test(KisPaintLayerTest TESTNAME krita-image-KisPaintLayerTest ${kis_paint_layer_test_SRCS})

target_link_libraries(KisPaintLayerTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_adjustment_layer_test_SRCS kis_adjustment_layer_test.cpp )
kde4_add_unit_test(KisAdjustmentLayerTest TESTNAME krita-image-KisAdjustmentLayerTest ${kis_adjustment_layer_test_SRCS})
target_link_libraries(KisAdjustmentLayerTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_annotation_test_SRCS kis_annotation_test.cpp )
kde4_add_unit_test(KisAnnotationTest TESTNAME krita-image-KisAnnotationTest ${kis_annotation_test_SRCS})
target_link_libraries(KisAnnotationTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_bookmarked_configuration_manager_test_SRCS kis_bookmarked_configuration_manager_test.cpp )
kde4_add_unit_test(KisBookmarkedConfigurationManagerTest TESTNAME krita-image-KisBookmarkedConfigurationManagerTest ${kis_bookmarked_configuration_manager_test_SRCS})
target_link_libraries(KisBookmarkedConfigurationManagerTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_change_profile_visitor_test_SRCS kis_change_profile_visitor_test.cpp )
kde4_add_unit_test(KisChangeProfileVisitorTest TESTNAME krita-image-KisChangeProfileVisitorTest ${kis_change_profile_visitor_test_SRCS})
target_link_libraries(KisChangeProfileVisitorTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_clone_layer_test_SRCS kis_clone_layer_test.cpp )
kde4_add_unit_test(KisCloneLayerTest TESTNAME krita-image-KisCloneLayerTest ${kis_clone_layer_test_SRCS})
target_link_libraries(KisCloneLayerTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_colorspace_convert_visitor_test_SRCS kis_colorspace_convert_visitor_test.cpp )
kde4_add_unit_test(KisColorspaceConvertVisitorTest TESTNAME krita-image-KisColorspaceConvertVisitorTest ${kis_colorspace_convert_visitor_test_SRCS})
target_link_libraries(KisColorspaceConvertVisitorTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_convolution_painter_test_SRCS kis_convolution_painter_test.cpp )
kde4_add_unit_test(KisConvolutionPainterTest TESTNAME krita-image-KisConvolutionPainterTest ${kis_convolution_painter_test_SRCS})
target_link_libraries(KisConvolutionPainterTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_crop_processing_visitor_test_SRCS kis_crop_processing_visitor_test.cpp )
kde4_add_unit_test(KisCropProcessingVisitorTest TESTNAME krita-image-KisCropProcessingVisitorTest ${kis_crop_processing_visitor_test_SRCS})
target_link_libraries(KisCropProcessingVisitorTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_processing_applicator_test_SRCS kis_processing_applicator_test.cpp )
kde4_add_unit_test(KisProcessingApplicatorTest TESTNAME krita-image-KisProcessingApplicatorTest ${kis_processing_applicator_test_SRCS})
target_link_libraries(KisProcessingApplicatorTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_datamanager_test_SRCS kis_datamanager_test.cpp )
kde4_add_unit_test(KisDatamanagerTest TESTNAME krita-image-KisDatamanagerTest ${kis_datamanager_test_SRCS})
target_link_libraries(KisDatamanagerTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_fill_painter_test_SRCS kis_fill_painter_test.cpp )
kde4_add_unit_test(KisFillPainterTest TESTNAME krita-image-KisFillPainterTest ${kis_fill_painter_test_SRCS})
target_link_libraries(KisFillPainterTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_filter_configuration_test_SRCS kis_filter_configuration_test.cpp )
kde4_add_unit_test(KisFilterConfigurationTest TESTNAME krita-image-KisFilterConfigurationTest ${kis_filter_configuration_test_SRCS})
target_link_libraries(KisFilterConfigurationTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_filter_test_SRCS kis_filter_test.cpp )
kde4_add_unit_test(KisFilterTest TESTNAME krita-image-KisFilterTest ${kis_filter_test_SRCS})
target_link_libraries(KisFilterTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_filter_processing_information_test_SRCS kis_filter_processing_information_test.cpp )
kde4_add_unit_test(KisFilterProcessingInformationTest TESTNAME krita-image-KisFilterProcessingInformationTest ${kis_filter_processing_information_test_SRCS})
target_link_libraries(KisFilterProcessingInformationTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_filter_registry_test_SRCS kis_filter_registry_test.cpp )
kde4_add_unit_test(KisFilterRegistryTest TESTNAME krita-image-KisFilterRegistryTest ${kis_filter_registry_test_SRCS})
target_link_libraries(KisFilterRegistryTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_filter_strategy_test_SRCS kis_filter_strategy_test.cpp )
kde4_add_unit_test(KisFilterStrategyTest TESTNAME krita-image-KisFilterStrategyTest ${kis_filter_strategy_test_SRCS})
target_link_libraries(KisFilterStrategyTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_gradient_painter_test_SRCS kis_gradient_painter_test.cpp )
kde4_add_unit_test(KisGradientPainterTest TESTNAME krita-image-KisGradientPainterTest ${kis_gradient_painter_test_SRCS})
target_link_libraries(KisGradientPainterTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_histogram_test_SRCS kis_histogram_test.cpp )
kde4_add_broken_unit_test(KisHistogramTest TESTNAME krita-image-KisHistogramTest ${kis_histogram_test_SRCS})
target_link_libraries(KisHistogramTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_image_commands_test_SRCS kis_image_commands_test.cpp )
kde4_add_unit_test(KisImageCommandsTest TESTNAME krita-image-KisImageCommandsTest ${kis_image_commands_test_SRCS})
target_link_libraries(KisImageCommandsTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_image_test_SRCS kis_image_test.cpp )
kde4_add_unit_test(KisImageTest TESTNAME krita-image-KisImageTest ${kis_image_test_SRCS})
target_link_libraries(KisImageTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_image_signal_router_test_SRCS kis_image_signal_router_test.cpp )
kde4_add_unit_test(KisImageSignalRouterTest TESTNAME krita-image-KisImageSignalRouterTest ${kis_image_signal_router_test_SRCS})
target_link_libraries(KisImageSignalRouterTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_iterators_ng_test_SRCS kis_iterators_ng_test.cpp )
kde4_add_unit_test(KisIteratorsNGTest TESTNAME krita-image-KisIteratorsNGTest ${kis_iterators_ng_test_SRCS})
target_link_libraries(KisIteratorsNGTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_iterator_benchmark_SRCS kis_iterator_benchmark.cpp )
kde4_add_unit_test(KisIteratorBenchmark TESTNAME krita-image-KisIteratorBenchmark ${kis_iterator_benchmark_SRCS})
target_link_libraries(KisIteratorBenchmark   kritaimage Qt5::Test)

########### next target ###############

set(kis_walkers_test_SRCS kis_walkers_test.cpp )
kde4_add_broken_unit_test(KisWalkersTest TESTNAME krita-image-KisWalkersTest ${kis_walkers_test_SRCS})
target_link_libraries(KisWalkersTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_async_merger_test_SRCS kis_async_merger_test.cpp )
kde4_add_broken_unit_test(KisAsyncMergerTest TESTNAME krita-image-KisAsyncMergerTest ${kis_async_merger_test_SRCS})
target_link_libraries(KisAsyncMergerTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_updater_context_test_SRCS kis_updater_context_test.cpp )
kde4_add_unit_test(KisUpdaterContextTest TESTNAME krita-image-KisUpdaterContextTest ${kis_updater_context_test_SRCS})
target_link_libraries(KisUpdaterContextTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_simple_update_queue_test_SRCS kis_simple_update_queue_test.cpp )
kde4_add_unit_test(KisSimpleUpdateQueueTest TESTNAME krita-image-KisSimpleUpdateQueueTest ${kis_simple_update_queue_test_SRCS})
target_link_libraries(KisSimpleUpdateQueueTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_update_scheduler_test_SRCS kis_update_scheduler_test.cpp )
kde4_add_broken_unit_test(KisUpdateSchedulerTest TESTNAME krita-image-KisUpdateSchedulerTest ${kis_update_scheduler_test_SRCS})
target_link_libraries(KisUpdateSchedulerTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_stroke_test_SRCS kis_stroke_test.cpp )
kde4_add_unit_test(KisStrokeTest TESTNAME krita-image-KisStrokeTest ${kis_stroke_test_SRCS})
target_link_libraries(KisStrokeTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_simple_stroke_strategy_test_SRCS kis_simple_stroke_strategy_test.cpp )
kde4_add_unit_test(KisSimpleStrokeStrategyTest TESTNAME krita-image-KisSimpleStrokeStrategyTest ${kis_simple_stroke_strategy_test_SRCS})
target_link_libraries(KisSimpleStrokeStrategyTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_stroke_strategy_undo_command_based_test_SRCS kis_stroke_strategy_undo_command_based_test.cpp )
kde4_add_unit_test(KisStrokeStrategyUndoCommandBasedTest TESTNAME krita-image-KisStrokeStrategyUndoCommandBasedTest ${kis_stroke_strategy_undo_command_based_test_SRCS})
target_link_libraries(KisStrokeStrategyUndoCommandBasedTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_strokes_queue_test_SRCS kis_strokes_queue_test.cpp )
kde4_add_unit_test(KisStrokesQueueTest TESTNAME krita-image-KisStrokesQueueTest ${kis_strokes_queue_test_SRCS})
target_link_libraries(KisStrokesQueueTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_queues_progress_updater_test_SRCS kis_queues_progress_updater_test.cpp )
kde4_add_broken_unit_test(KisQueuesProgressUpdaterTest TESTNAME krita-image-KisQueuesProgressUpdaterTest ${kis_queues_progress_updater_test_SRCS})
target_link_libraries(KisQueuesProgressUpdaterTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_macro_test_SRCS kis_macro_test.cpp )
kde4_add_unit_test(KisMacroTest TESTNAME krita-image-KisMacroTest ${kis_macro_test_SRCS})
target_link_libraries(KisMacroTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_mask_test_SRCS kis_mask_test.cpp )
kde4_add_unit_test(KisMaskTest TESTNAME krita-image-KisMaskTest ${kis_mask_test_SRCS})
target_link_libraries(KisMaskTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_math_toolbox_test_SRCS kis_math_toolbox_test.cpp )
kde4_add_unit_test(KisMathToolboxTest TESTNAME krita-image-KisMathToolboxTest ${kis_math_toolbox_test_SRCS})
target_link_libraries(KisMathToolboxTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_name_server_test_SRCS kis_name_server_test.cpp )
kde4_add_unit_test(KisNameServerTest TESTNAME krita-image-KisNameServerTest ${kis_name_server_test_SRCS})
target_link_libraries(KisNameServerTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_node_commands_test_SRCS kis_node_commands_test.cpp )
kde4_add_unit_test(KisNodeCommandsTest TESTNAME krita-image-KisNodeCommandsTest ${kis_node_commands_test_SRCS})
target_link_libraries(KisNodeCommandsTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_node_graph_listener_test_SRCS kis_node_graph_listener_test.cpp )
kde4_add_unit_test(KisNodeGraphListenerTest TESTNAME krita-image-KisNodeGraphListenerTest ${kis_node_graph_listener_test_SRCS})
target_link_libraries(KisNodeGraphListenerTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_node_visitor_test_SRCS kis_node_visitor_test.cpp )
kde4_add_unit_test(KisNodeVisitorTest TESTNAME krita-image-KisNodeVisitorTest ${kis_node_visitor_test_SRCS})
target_link_libraries(KisNodeVisitorTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_paint_information_test_SRCS kis_paint_information_test.cpp )
kde4_add_unit_test(KisPaintInformationTest TESTNAME krita-image-KisPaintInformationTest ${kis_paint_information_test_SRCS})
target_link_libraries(KisPaintInformationTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_paintop_test_SRCS kis_paintop_test.cpp )
kde4_add_unit_test(KisPaintopTest TESTNAME krita-image-KisPaintopTest ${kis_paintop_test_SRCS})
target_link_libraries(KisPaintopTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_pattern_test_SRCS kis_pattern_test.cpp )
kde4_add_unit_test(KoPatternTest TESTNAME krita-image-KoPatternTest ${kis_pattern_test_SRCS})
target_link_libraries(KoPatternTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_recorded_action_factory_registry_test_SRCS kis_recorded_action_factory_registry_test.cpp )
kde4_add_unit_test(KisRecordedActionFactoryRegistryTest TESTNAME krita-image-KisRecordedActionFactoryRegistryTest ${kis_recorded_action_factory_registry_test_SRCS})
target_link_libraries(KisRecordedActionFactoryRegistryTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_recorded_action_test_SRCS kis_recorded_action_test.cpp )
kde4_add_unit_test(KisRecordedActionTest TESTNAME krita-image-KisRecordedActionTest ${kis_recorded_action_test_SRCS})
target_link_libraries(KisRecordedActionTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_recorded_filter_action_test_SRCS kis_recorded_filter_action_test.cpp )
kde4_add_unit_test(KisRecordedFilterActionTest TESTNAME krita-image-KisRecordedFilterActionTest ${kis_recorded_filter_action_test_SRCS})
target_link_libraries(KisRecordedFilterActionTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_selection_mask_test_SRCS kis_selection_mask_test.cpp )
kde4_add_unit_test(KisSelectionMaskTest TESTNAME krita-image-KisSelectionMaskTest ${kis_selection_mask_test_SRCS})
target_link_libraries(KisSelectionMaskTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_shared_ptr_test_SRCS kis_shared_ptr_test.cpp )
kde4_add_unit_test(KisSharedPtrTest TESTNAME krita-image-KisSharedPtrTest ${kis_shared_ptr_test_SRCS})
target_link_libraries(KisSharedPtrTest   kritaimage Qt5::Test)

########### next target ###############
# kisdoc dep
#set(kis_transform_worker_test_SRCS kis_transform_worker_test.cpp )
#kde4_add_unit_test(KisTransformWorkerTest TESTNAME krita-image-KisTransformWorkerTest ${kis_transform_worker_test_SRCS})
#target_link_libraries(KisTransformWorkerTest   kritaimage Qt5::Test)

########### next target ###############
# kisdoc
#set(kis_perspective_transform_worker_test_SRCS kis_perspective_transform_worker_test.cpp )
#kde4_add_unit_test(KisPerspectiveTransformWorkerTest TESTNAME krita-image-KisPerspectiveTransformWorkerTest ${kis_perspective_transform_worker_test_SRCS})
#target_link_libraries(KisPerspectiveTransformWorkerTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_bsplines_test_SRCS kis_bsplines_test.cpp )
kde4_add_unit_test(KisBSplinesTest TESTNAME krita-image-KisBSplinesTest ${kis_bsplines_test_SRCS})
target_link_libraries(KisBSplinesTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_warp_transform_worker_test_SRCS  kis_warp_transform_worker_test.cpp)
kde4_add_unit_test(KisWarpTransformWorkerTest TESTNAME krita-image-KisWarpTransformWorkerTest ${kis_warp_transform_worker_test_SRCS})
target_link_libraries(KisWarpTransformWorkerTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_cage_transform_worker_test_SRCS  kis_cage_transform_worker_test.cpp)
kde4_add_broken_unit_test(KisCageTransformWorkerTest TESTNAME krita-image-KisCageTransformWorkerTest ${kis_cage_transform_worker_test_SRCS})
target_link_libraries(KisCageTransformWorkerTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_liquify_transform_worker_test_SRCS  kis_liquify_transform_worker_test.cpp)
kde4_add_unit_test(KisLiquifyTransformWorkerTest TESTNAME krita-image-KisLiquifyTransformWorkerTest ${kis_liquify_transform_worker_test_SRCS})
target_link_libraries(KisLiquifyTransformWorkerTest   kritaimage Qt5::Test)


########### next target ###############

set(kis_transparency_mask_test_SRCS kis_transparency_mask_test.cpp )
kde4_add_unit_test(KisTransparencyMaskTest TESTNAME krita-image-KisTransparencyMaskTest ${kis_transparency_mask_test_SRCS})
target_link_libraries(KisTransparencyMaskTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_types_test_SRCS kis_types_test.cpp )
kde4_add_unit_test(KisTypesTest TESTNAME krita-image-KisTypesTest ${kis_types_test_SRCS})
target_link_libraries(KisTypesTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_vec_test_SRCS kis_vec_test.cpp )
kde4_add_unit_test(KisVecTest TESTNAME krita-image-KisVecTest ${kis_vec_test_SRCS})
target_link_libraries(KisVecTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_filter_config_widget_test_SRCS kis_filter_config_widget_test.cpp )
kde4_add_unit_test(KisFilterConfigWidgetTest TESTNAME krita-image-KisFilterConfigWidgetTest ${kis_filter_config_widget_test_SRCS})
target_link_libraries(KisFilterConfigWidgetTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_meta_data_test_SRCS kis_meta_data_test.cpp )
kde4_add_broken_unit_test(KisMetaDataTest TESTNAME krita-image-KisMetaDataTest ${kis_meta_data_test_SRCS})
target_link_libraries(KisMetaDataTest  kritaimage Qt5::Test)

########### next target ###############

set(kis_random_generator_test_SRCS kis_random_generator_test.cpp )
kde4_add_broken_unit_test(KisRandomGeneratorTest TESTNAME krita-image-KisRandomGeneratorTest ${kis_random_generator_test_SRCS})
target_link_libraries(KisRandomGeneratorTest  kritaimage Qt5::Test)

########### next target ###############

set(kis_mask_generator_test_SRCS kis_mask_generator_test.cpp )
kde4_add_unit_test(KisMaskGeneratorTest TESTNAME krita-image-KisMaskGeneratorTest ${kis_mask_generator_test_SRCS})
target_link_libraries(KisMaskGeneratorTest  kritaimage Qt5::Test)

########### next target ###############

#set(kis_cs_conversion_test_SRCS kis_cs_conversion_test.cpp )
#kde4_add_unit_test(KisCsConversionTest TESTNAME krita-image-KisCsConversionTest ${kis_cs_conversion_test_SRCS})
#target_link_libraries(KisCsConversionTest  kritaimage Qt5::Test)

########### next target ###############

set(kis_cubic_curve_test_SRCS kis_cubic_curve_test.cpp )
kde4_add_unit_test(KisCubicCurveTest TESTNAME krita-image-KisCubicCurveTest ${kis_cubic_curve_test_SRCS})
target_link_libraries(KisCubicCurveTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_node_query_path_test_SRCS kis_node_query_path_test.cpp )
kde4_add_unit_test(KisNodeQueryPathTest TESTNAME krita-image-KisNodeQueryPathTest ${kis_node_query_path_test_SRCS})
target_link_libraries(KisNodeQueryPathTest   kritaimage Qt5::Test)

########### next target ###############
# kisdoc
#set(kis_processings_test_SRCS kis_processings_test.cpp )
#kde4_add_unit_test(KisProcessingsTest TESTNAME krita-image-KisProcessingsTest ${kis_processings_test_SRCS})
#target_link_libraries(KisProcessingsTest   kritaimage Qt5::Test)


########### next target ###############

set(kis_fixed_point_maths_test_SRCS kis_fixed_point_maths_test.cpp )
kde4_add_unit_test(KisFixedPointMathsTest TESTNAME krita-image-KisFixedPointMathsTest ${kis_fixed_point_maths_test_SRCS})
target_link_libraries(KisFixedPointMathsTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_filter_weights_buffer_test_SRCS kis_filter_weights_buffer_test.cpp )
kde4_add_unit_test(KisFilterWeightsBufferTest TESTNAME krita-image-KisFilterWeightsBufferTest ${kis_filter_weights_buffer_test_SRCS})
target_link_libraries(KisFilterWeightsBufferTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_filter_weights_applicator_test_SRCS kis_filter_weights_applicator_test.cpp )
kde4_add_unit_test(KisFilterWeightsApplicatorTest TESTNAME krita-image-KisFilterWeightsApplicatorTest ${kis_filter_weights_applicator_test_SRCS})
target_link_libraries(KisFilterWeightsApplicatorTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_fill_interval_test_SRCS kis_fill_interval_test.cpp )
kde4_add_unit_test(KisFillIntervalTest TESTNAME krita-image-FillInterval-Test ${kis_fill_interval_test_SRCS})
target_link_libraries(KisFillIntervalTest   kritaimage Qt5::Test)


########### next target ###############

set(kis_fill_interval_map_test_SRCS kis_fill_interval_map_test.cpp )
kde4_add_unit_test(KisFillIntervalMapTest TESTNAME krita-image-FillIntervalMap-Test ${kis_fill_interval_map_test_SRCS})
target_link_libraries(KisFillIntervalMapTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_scanline_fill_test_SRCS kis_scanline_fill_test.cpp )
kde4_add_unit_test(KisScanlineFillTest TESTNAME krita-image-ScanlineFill-Test ${kis_scanline_fill_test_SRCS})
target_link_libraries(KisScanlineFillTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_keyframing_test_SRCS kis_keyframing_test.cpp )
kde4_add_broken_unit_test(KisKeyframingTest TESTNAME krita-image-Keyframing-Test ${kis_keyframing_test_SRCS})
target_link_libraries(KisKeyframingTest  ${KDE4_KDEUI_LIBS} kritaimage ${QT_QTTEST_LIBRARY})

########### next target ###############

set(kis_psd_layer_style_test_SRCS kis_psd_layer_style_test.cpp )
kde4_add_unit_test(KisPSDLayerStyleTest TESTNAME krita-image-PSDLayerStyle-Test ${kis_psd_layer_style_test_SRCS})
target_link_libraries(KisPSDLayerStyleTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_dom_utils_test_SRCS kis_dom_utils_test.cpp )
kde4_add_unit_test(KisDomUtilsTest TESTNAME krita-image-DomUtils-Test ${kis_dom_utils_test_SRCS})
target_link_libraries(KisDomUtilsTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_image_animation_interface_test_SRCS kis_image_animation_interface_test.cpp )
kde4_add_broken_unit_test(KisImageAnimationInterfaceTest TESTNAME krita-image-ImageAnimationInterface-Test ${kis_image_animation_interface_test_SRCS})
target_link_libraries(KisImageAnimationInterfaceTest  ${KDE4_KDEUI_LIBS} kritaimage ${QT_QTTEST_LIBRARY})
########### next target ###############

set(kis_onion_skin_compositor_test_SRCS kis_onion_skin_compositor_test.cpp )
kde4_add_broken_unit_test(KisOnionSkinCompositorTest TESTNAME krita-image-OnionSkinCompositor-Test ${kis_onion_skin_compositor_test_SRCS})
target_link_libraries(KisOnionSkinCompositorTest  ${KDE4_KDEUI_LIBS} kritaimage ${QT_QTTEST_LIBRARY})

########### next target ###############

set(kis_layer_styles_test_SRCS kis_layer_styles_test.cpp )
kde4_add_broken_unit_test(KisLayerStylesTest TESTNAME krita-image-LayerStylesTest  ${kis_layer_styles_test_SRCS})
target_link_libraries(KisLayerStylesTest    kritaimage Qt5::Test)

########### next target ###############

set(kis_layer_style_projection_plane_test_SRCS kis_layer_style_projection_plane_test.cpp )
kde4_add_unit_test(KisLayerStyleProjectionPlaneTest TESTNAME kritaimage-layer_style_projection_plane_test ${kis_layer_style_projection_plane_test_SRCS})
target_link_libraries(KisLayerStyleProjectionPlaneTest   kritaimage Qt5::Test)

########### next target ###############

set(kis_layer_style_filter_environment_test_SRCS kis_layer_style_filter_environment_test.cpp )
kde4_add_unit_test(KisLayerStyleFilterEnvironmentTest TESTNAME kritaimage-layer_style_filter_environment_test ${kis_layer_style_filter_environment_test_SRCS})
target_link_libraries(KisLayerStyleFilterEnvironmentTest  ${KDE4_KDEUI_LIBS} kritaimage ${QT_QTTEST_LIBRARY})


########### next target ###############

set(kis_layer_style_filter_environment_test_SRCS kis_layer_style_filter_environment_test.cpp )
kde4_add_unit_test(KisLayerStyleFilterEnvironmentTest TESTNAME kritaimage-layer_style_filter_environment_test ${kis_layer_style_filter_environment_test_SRCS})
target_link_libraries(KisLayerStyleFilterEnvironmentTest  ${KDE4_KDEUI_LIBS} kritaimage ${QT_QTTEST_LIBRARY})


########### next target ###############
# image/tests cannot use stuff that needs kisdocument
#set(kis_projection_leaf_test_SRCS kis_projection_leaf_test.cpp )
#kde4_add_unit_test(KisProjectionLeafTest TESTNAME kritaimage-projection_leaf_test ${kis_projection_leaf_test_SRCS})
#target_link_libraries(KisProjectionLeafTest kritaimage ${QT_QTTEST_LIBRARY})

########### next target ###############

set(kis_lod_capable_layer_offset_test_SRCS kis_lod_capable_layer_offset_test.cpp )
kde4_add_unit_test(KisLodCapableLayerOffsetTest TESTNAME kritaimage-lod_capable_layer_offset_test ${kis_lod_capable_layer_offset_test_SRCS})
target_link_libraries(KisLodCapableLayerOffsetTest kritaimage ${QT_QTTEST_LIBRARY})

########### next target ###############

set(kis_asl_parser_test_SRCS kis_asl_parser_test.cpp )
kde4_add_unit_test(KisAslParserTest TESTNAME kritalibpsd-asl_parser_test ${kis_asl_parser_test_SRCS})
target_link_libraries(KisAslParserTest kritapsd kritapigment kritawidgetutils  ${QT_QTXML_LIBRARY} Qt5::Test)

