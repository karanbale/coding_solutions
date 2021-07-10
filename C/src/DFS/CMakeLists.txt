cmake_minimum_required(VERSION 3.14)

set(component_name "DFS")

set(srcs
    70_climbStairs.c
    94_binaryTreeInOrderTraversal.c
    112_pathSum.c
    124_maximumBinaryTreePathSumDFS.c
    130_surroundedRegionsDFS.c
    145_binaryTreePostOrderTraversal.c
    145_binaryTreePostOrderTraversalStack.c
    200_numberOfIslandsDFS.c
    230_kthSmallestElementInBSTStack.c
    286_wallsAndGatesDFS.c
    463_islandPerimeter.c
    486_predictTheWinner.c
    559_maximumDepthOfN-aryTreeDFS.c
    572_subtreeOfAnotherTree.c
    671_secondMinimumNodeInABinaryTree.c
    695_maxAreaOfIsland.c
    980_uniquePaths3.c
    1306_jumpGame3DFS.c
)

target_include_directories(${LIBRARY_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:/include>
    PRIVATE
        ${PROJECT_SOURCE_DIR}/C/include/DFS/
        ${PROJECT_SOURCE_DIR}/C/src/common_utils/
)

add_lib_sources(${component_name} "${srcs}")
