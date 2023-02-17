(module
  (type (;0;) (func (param i32) (result i32)))
  (type (;1;) (func (param i32 i32) (result i32)))
  (type (;2;) (func (result i32)))
  (type (;3;) (func (param i32 i32 i32) (result i32)))
  (type (;4;) (func (param i32 i32)))
  (type (;5;) (func (param i32 i32 i32 i32) (result i32)))
  (type (;6;) (func (param i32)))
  (func $getLength (type 0) (param i32) (result i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 1
    local.get 0
    i32.store offset=8
    block  ;; label = @1
      block  ;; label = @2
        local.get 1
        i32.load offset=8
        i32.const 0
        i32.eq
        i32.const 1
        i32.and
        i32.eqz
        br_if 0 (;@2;)
        local.get 1
        i32.const 0
        i32.store offset=12
        br 1 (;@1;)
      end
      local.get 1
      local.get 1
      i32.load offset=8
      i32.load offset=4
      i32.store offset=12
    end
    local.get 1
    i32.load offset=12)
  (func $createLst (type 1) (param i32 i32) (result i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 2
    global.set 0
    local.get 2
    local.get 0
    i32.store offset=12
    local.get 2
    local.get 1
    i32.store offset=8
    local.get 2
    i32.const 12
    call $malloc
    i32.store offset=4
    local.get 2
    i32.load offset=4
    local.get 2
    i32.load offset=12
    i32.store
    local.get 2
    i32.load offset=4
    local.get 2
    i32.load offset=8
    i32.store offset=8
    local.get 2
    i32.load offset=8
    call $getLength
    local.set 0
    local.get 2
    i32.load offset=4
    local.get 0
    i32.const 1
    i32.add
    i32.store offset=4
    local.get 2
    i32.load offset=4
    local.set 0
    local.get 2
    i32.const 16
    i32.add
    global.set 0
    local.get 0)
  (func $addToFront (type 1) (param i32 i32) (result i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 2
    global.set 0
    local.get 2
    local.get 0
    i32.store offset=12
    local.get 2
    local.get 1
    i32.store offset=8
    local.get 2
    i32.load offset=12
    local.get 2
    i32.load offset=8
    call $createLst
    local.set 0
    local.get 2
    i32.const 16
    i32.add
    global.set 0
    local.get 0)
  (func $emptyLst (type 2) (result i32)
    i32.const 0)
  (func $createNode (type 3) (param i32 i32 i32) (result i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 3
    global.set 0
    local.get 3
    local.get 0
    i32.store offset=12
    local.get 3
    local.get 1
    i32.store offset=8
    local.get 3
    local.get 2
    i32.store offset=4
    local.get 3
    i32.const 12
    call $malloc
    i32.store
    local.get 3
    i32.load
    local.get 3
    i32.load offset=12
    i32.store
    local.get 3
    i32.load
    local.get 3
    i32.load offset=4
    i32.store offset=8
    local.get 3
    i32.load
    local.get 3
    i32.load offset=8
    i32.store offset=4
    local.get 3
    i32.load
    local.set 0
    local.get 3
    i32.const 16
    i32.add
    global.set 0
    local.get 0)
  (func $copyRawNode (type 0) (param i32) (result i32)
    (local i32 i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 1
    global.set 0
    local.get 1
    local.get 0
    i32.store offset=12
    local.get 1
    i32.load offset=12
    i32.load
    local.set 0
    local.get 1
    i32.load offset=12
    i32.load offset=4
    local.set 2
    call $emptyLst
    drop
    local.get 0
    local.get 2
    i32.const 0
    call $createNode
    local.set 0
    local.get 1
    i32.const 16
    i32.add
    global.set 0
    local.get 0)
  (func $addNghbr (type 4) (param i32 i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 2
    global.set 0
    local.get 2
    local.get 0
    i32.store offset=12
    local.get 2
    local.get 1
    i32.store offset=8
    local.get 2
    local.get 2
    i32.load offset=12
    i32.load offset=8
    i32.store offset=4
    local.get 2
    i32.load offset=8
    local.get 2
    i32.load offset=4
    call $addToFront
    local.set 0
    local.get 2
    i32.load offset=12
    local.get 0
    i32.store offset=8
    local.get 2
    i32.const 16
    i32.add
    global.set 0)
  (func $createGraph (type 3) (param i32 i32 i32) (result i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 3
    global.set 0
    local.get 3
    local.get 0
    i32.store offset=12
    local.get 3
    local.get 1
    i32.store offset=8
    local.get 3
    local.get 2
    i32.store offset=4
    local.get 3
    i32.const 12
    call $malloc
    i32.store
    local.get 3
    i32.load
    local.get 3
    i32.load offset=12
    i32.store
    local.get 3
    i32.load
    local.get 3
    i32.load offset=8
    i32.store offset=4
    local.get 3
    i32.load
    local.get 3
    i32.load offset=4
    i32.store offset=8
    local.get 3
    i32.load
    local.set 0
    local.get 3
    i32.const 16
    i32.add
    global.set 0
    local.get 0)
  (func $graphTranspose (type 0) (param i32) (result i32)
    (local i32)
    global.get 0
    i32.const 48
    i32.sub
    local.tee 1
    global.set 0
    local.get 1
    local.get 0
    i32.store offset=44
    local.get 1
    local.get 1
    i32.load offset=44
    i32.load offset=8
    i32.store offset=40
    local.get 1
    local.get 1
    i32.load offset=44
    i32.load
    i32.store offset=36
    local.get 1
    local.get 1
    i32.load offset=44
    i32.load offset=4
    i32.store offset=32
    local.get 1
    local.get 1
    i32.load offset=36
    i32.const 1
    i32.add
    i32.const 2
    i32.shl
    call $malloc
    i32.store offset=28
    local.get 1
    i32.const 1
    i32.store offset=24
    block  ;; label = @1
      loop  ;; label = @2
        local.get 1
        i32.load offset=24
        local.get 1
        i32.load offset=36
        i32.le_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 1
        local.get 1
        i32.load offset=40
        local.get 1
        i32.load offset=24
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.store offset=20
        local.get 1
        local.get 1
        i32.load offset=20
        call $copyRawNode
        i32.store offset=16
        local.get 1
        i32.load offset=28
        local.get 1
        i32.load offset=24
        i32.const 2
        i32.shl
        i32.add
        local.get 1
        i32.load offset=16
        i32.store
        local.get 1
        local.get 1
        i32.load offset=24
        i32.const 1
        i32.add
        i32.store offset=24
        br 0 (;@2;)
      end
    end
    local.get 1
    i32.const 1
    i32.store offset=12
    block  ;; label = @1
      loop  ;; label = @2
        local.get 1
        i32.load offset=12
        local.get 1
        i32.load offset=36
        i32.le_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 1
        local.get 1
        i32.load offset=40
        local.get 1
        i32.load offset=12
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.store offset=8
        local.get 1
        local.get 1
        i32.load offset=8
        i32.load offset=8
        i32.store offset=4
        block  ;; label = @3
          loop  ;; label = @4
            local.get 1
            i32.load offset=4
            i32.const 0
            i32.ne
            i32.const 1
            i32.and
            i32.eqz
            br_if 1 (;@3;)
            local.get 1
            local.get 1
            i32.load offset=4
            i32.load
            i32.store
            local.get 1
            i32.load offset=28
            local.get 1
            i32.load
            i32.const 2
            i32.shl
            i32.add
            i32.load
            local.get 1
            i32.load offset=8
            i32.load
            call $addNghbr
            local.get 1
            local.get 1
            i32.load offset=4
            i32.load offset=8
            i32.store offset=4
            br 0 (;@4;)
          end
        end
        local.get 1
        local.get 1
        i32.load offset=12
        i32.const 1
        i32.add
        i32.store offset=12
        br 0 (;@2;)
      end
    end
    local.get 1
    i32.load offset=36
    local.get 1
    i32.load offset=32
    local.get 1
    i32.load offset=28
    call $createGraph
    local.set 0
    local.get 1
    i32.const 48
    i32.add
    global.set 0
    local.get 0)
  (func $getNghbrs (type 1) (param i32 i32) (result i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 2
    local.get 0
    i32.store offset=12
    local.get 2
    local.get 1
    i32.store offset=8
    local.get 2
    i32.load offset=12
    i32.load offset=8
    local.get 2
    i32.load offset=8
    i32.const 2
    i32.shl
    i32.add
    i32.load
    i32.load offset=8)
  (func $createDFSInfo (type 0) (param i32) (result i32)
    (local i32)
    global.get 0
    i32.const 48
    i32.sub
    local.tee 1
    global.set 0
    local.get 1
    local.get 0
    i32.store offset=44
    local.get 1
    i32.const 36
    call $malloc
    i32.store offset=40
    local.get 1
    i32.load offset=40
    local.get 1
    i32.load offset=44
    i32.store
    local.get 1
    local.get 1
    i32.load offset=44
    i32.load
    i32.const 1
    i32.add
    i32.store offset=36
    local.get 1
    local.get 1
    i32.load offset=36
    i32.const 2
    i32.shl
    call $malloc
    i32.store offset=32
    local.get 1
    local.get 1
    i32.load offset=36
    i32.const 2
    i32.shl
    call $malloc
    i32.store offset=28
    local.get 1
    local.get 1
    i32.load offset=36
    i32.const 4
    call $calloc
    i32.store offset=24
    local.get 1
    local.get 1
    i32.load offset=36
    i32.const 2
    i32.shl
    call $malloc
    i32.store offset=20
    local.get 1
    local.get 1
    i32.load offset=44
    i32.load
    i32.const 2
    i32.shl
    call $malloc
    i32.store offset=16
    local.get 1
    local.get 1
    i32.load offset=44
    i32.load
    i32.const 2
    i32.shl
    call $malloc
    i32.store offset=12
    local.get 1
    i32.load offset=40
    local.get 1
    i32.load offset=32
    i32.store offset=8
    local.get 1
    i32.load offset=40
    local.get 1
    i32.load offset=28
    i32.store offset=12
    local.get 1
    i32.load offset=40
    local.get 1
    i32.load offset=24
    i32.store offset=16
    local.get 1
    i32.load offset=40
    local.get 1
    i32.load offset=20
    i32.store offset=20
    local.get 1
    i32.load offset=40
    local.get 1
    i32.load offset=16
    i32.store offset=24
    local.get 1
    i32.load offset=40
    i32.const 0
    i32.store offset=4
    local.get 1
    i32.load offset=40
    local.get 1
    i32.load offset=12
    i32.store offset=28
    local.get 1
    i32.load offset=40
    i32.const -1
    i32.store offset=32
    local.get 1
    i32.load offset=40
    local.set 0
    local.get 1
    i32.const 48
    i32.add
    global.set 0
    local.get 0)
  (func $addDFSTree (type 4) (param i32 i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 2
    global.set 0
    local.get 2
    local.get 0
    i32.store offset=12
    local.get 2
    local.get 1
    i32.store offset=8
    local.get 2
    local.get 2
    i32.load offset=12
    i32.load offset=32
    i32.store offset=4
    local.get 2
    local.get 2
    i32.load offset=4
    i32.const 1
    i32.add
    i32.store offset=4
    local.get 2
    i32.load offset=12
    local.get 2
    i32.load offset=4
    i32.store offset=32
    local.get 2
    i32.load offset=8
    local.set 0
    call $emptyLst
    drop
    local.get 2
    local.get 0
    i32.const 0
    call $createLst
    i32.store
    local.get 2
    i32.load offset=12
    i32.load offset=28
    local.get 2
    i32.load offset=4
    i32.const 2
    i32.shl
    i32.add
    local.get 2
    i32.load
    i32.store
    local.get 2
    i32.const 16
    i32.add
    global.set 0)
  (func $extendCurDFSTree (type 4) (param i32 i32)
    (local i32)
    global.get 0
    i32.const 32
    i32.sub
    local.tee 2
    global.set 0
    local.get 2
    local.get 0
    i32.store offset=28
    local.get 2
    local.get 1
    i32.store offset=24
    local.get 2
    local.get 2
    i32.load offset=28
    i32.load offset=32
    i32.store offset=20
    local.get 2
    local.get 2
    i32.load offset=28
    i32.load offset=28
    local.get 2
    i32.load offset=20
    i32.const 2
    i32.shl
    i32.add
    i32.load
    i32.store offset=16
    local.get 2
    local.get 2
    i32.load offset=24
    local.get 2
    i32.load offset=16
    call $addToFront
    i32.store offset=12
    local.get 2
    i32.load offset=28
    i32.load offset=28
    local.get 2
    i32.load offset=20
    i32.const 2
    i32.shl
    i32.add
    local.get 2
    i32.load offset=12
    i32.store
    local.get 2
    i32.const 32
    i32.add
    global.set 0)
  (func $updateLastFinishTime (type 4) (param i32 i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 2
    local.get 0
    i32.store offset=12
    local.get 2
    local.get 1
    i32.store offset=8
    local.get 2
    local.get 2
    i32.load offset=12
    i32.load offset=4
    i32.store offset=4
    local.get 2
    i32.load offset=12
    i32.load offset=24
    local.get 2
    i32.load offset=4
    i32.const 2
    i32.shl
    i32.add
    local.get 2
    i32.load offset=8
    i32.store
    local.get 2
    i32.load offset=12
    local.get 2
    i32.load offset=4
    i32.const 1
    i32.add
    i32.store offset=4)
  (func $visit (type 5) (param i32 i32 i32 i32) (result i32)
    (local i32)
    global.get 0
    i32.const 32
    i32.sub
    local.tee 4
    global.set 0
    local.get 4
    local.get 0
    i32.store offset=24
    local.get 4
    local.get 1
    i32.store offset=20
    local.get 4
    local.get 2
    i32.store offset=16
    local.get 4
    local.get 3
    i32.store offset=12
    block  ;; label = @1
      block  ;; label = @2
        local.get 4
        i32.load offset=20
        i32.load offset=16
        local.get 4
        i32.load offset=16
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.eqz
        br_if 0 (;@2;)
        i32.const 1036
        i32.const 0
        call $printf
        drop
        local.get 4
        i32.const -1
        i32.store offset=28
        br 1 (;@1;)
      end
      local.get 4
      i32.load offset=20
      i32.load offset=16
      local.get 4
      i32.load offset=16
      i32.const 2
      i32.shl
      i32.add
      i32.const 1
      i32.store
      local.get 4
      i32.load offset=20
      i32.load offset=8
      local.get 4
      i32.load offset=16
      i32.const 2
      i32.shl
      i32.add
      local.get 4
      i32.load offset=12
      i32.store
      local.get 4
      local.get 4
      i32.load offset=12
      i32.const 1
      i32.add
      i32.store offset=12
      local.get 4
      local.get 4
      i32.load offset=24
      local.get 4
      i32.load offset=16
      call $getNghbrs
      i32.store offset=8
      block  ;; label = @2
        loop  ;; label = @3
          local.get 4
          i32.load offset=8
          i32.const 0
          i32.ne
          i32.const 1
          i32.and
          i32.eqz
          br_if 1 (;@2;)
          local.get 4
          local.get 4
          i32.load offset=8
          i32.load
          i32.store offset=4
          block  ;; label = @4
            local.get 4
            i32.load offset=20
            i32.load offset=16
            local.get 4
            i32.load offset=4
            i32.const 2
            i32.shl
            i32.add
            i32.load
            br_if 0 (;@4;)
            local.get 4
            i32.load offset=20
            local.get 4
            i32.load offset=4
            call $extendCurDFSTree
            local.get 4
            i32.load offset=20
            i32.load offset=20
            local.get 4
            i32.load offset=4
            i32.const 2
            i32.shl
            i32.add
            local.get 4
            i32.load offset=16
            i32.store
            local.get 4
            local.get 4
            i32.load offset=24
            local.get 4
            i32.load offset=20
            local.get 4
            i32.load offset=4
            local.get 4
            i32.load offset=12
            call $visit
            i32.store offset=12
          end
          local.get 4
          local.get 4
          i32.load offset=8
          i32.load offset=8
          i32.store offset=8
          br 0 (;@3;)
        end
      end
      local.get 4
      i32.load offset=20
      i32.load offset=12
      local.get 4
      i32.load offset=16
      i32.const 2
      i32.shl
      i32.add
      local.get 4
      i32.load offset=12
      i32.store
      local.get 4
      i32.load offset=20
      local.get 4
      i32.load offset=16
      call $updateLastFinishTime
      local.get 4
      local.get 4
      i32.load offset=12
      i32.const 1
      i32.add
      i32.store offset=12
      local.get 4
      local.get 4
      i32.load offset=12
      i32.store offset=28
    end
    local.get 4
    i32.load offset=28
    local.set 0
    local.get 4
    i32.const 32
    i32.add
    global.set 0
    local.get 0)
  (func $dfs (type 1) (param i32 i32) (result i32)
    (local i32)
    global.get 0
    i32.const 32
    i32.sub
    local.tee 2
    global.set 0
    local.get 2
    local.get 0
    i32.store offset=28
    local.get 2
    local.get 1
    i32.store offset=24
    local.get 2
    local.get 2
    i32.load offset=28
    call $createDFSInfo
    i32.store offset=20
    local.get 2
    local.get 2
    i32.load offset=28
    i32.load
    i32.store offset=16
    local.get 2
    i32.const 1
    i32.store offset=12
    block  ;; label = @1
      local.get 2
      i32.load offset=24
      i32.const 0
      i32.eq
      i32.const 1
      i32.and
      i32.eqz
      br_if 0 (;@1;)
      local.get 2
      local.get 2
      i32.load offset=16
      i32.const 2
      i32.shl
      call $malloc
      i32.store offset=24
      local.get 2
      i32.const 0
      i32.store offset=8
      block  ;; label = @2
        loop  ;; label = @3
          local.get 2
          i32.load offset=8
          local.get 2
          i32.load offset=16
          i32.lt_s
          i32.const 1
          i32.and
          i32.eqz
          br_if 1 (;@2;)
          local.get 2
          i32.load offset=24
          local.get 2
          i32.load offset=8
          i32.const 2
          i32.shl
          i32.add
          local.get 2
          i32.load offset=8
          i32.const 1
          i32.add
          i32.store
          local.get 2
          local.get 2
          i32.load offset=8
          i32.const 1
          i32.add
          i32.store offset=8
          br 0 (;@3;)
        end
      end
    end
    local.get 2
    i32.const 0
    i32.store offset=4
    block  ;; label = @1
      loop  ;; label = @2
        local.get 2
        i32.load offset=4
        local.get 2
        i32.load offset=16
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 2
        local.get 2
        i32.load offset=24
        local.get 2
        i32.load offset=4
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.store
        block  ;; label = @3
          local.get 2
          i32.load offset=20
          i32.load offset=16
          local.get 2
          i32.load
          i32.const 2
          i32.shl
          i32.add
          i32.load
          br_if 0 (;@3;)
          local.get 2
          i32.load offset=20
          i32.load offset=20
          local.get 2
          i32.load
          i32.const 2
          i32.shl
          i32.add
          i32.const -1
          i32.store
          local.get 2
          i32.load offset=20
          local.get 2
          i32.load
          call $addDFSTree
          local.get 2
          local.get 2
          i32.load offset=28
          local.get 2
          i32.load offset=20
          local.get 2
          i32.load
          local.get 2
          i32.load offset=12
          call $visit
          i32.store offset=12
        end
        local.get 2
        local.get 2
        i32.load offset=4
        i32.const 1
        i32.add
        i32.store offset=4
        br 0 (;@2;)
      end
    end
    local.get 2
    i32.load offset=20
    local.set 0
    local.get 2
    i32.const 32
    i32.add
    global.set 0
    local.get 0)
  (func $createPInfo (type 5) (param i32 i32 i32 i32) (result i32)
    (local i32)
    global.get 0
    i32.const 32
    i32.sub
    local.tee 4
    global.set 0
    local.get 4
    local.get 0
    i32.store offset=28
    local.get 4
    local.get 1
    i32.store offset=24
    local.get 4
    local.get 2
    i32.store offset=20
    local.get 4
    local.get 3
    i32.store offset=16
    local.get 4
    i32.const 16
    call $malloc
    i32.store offset=12
    local.get 4
    i32.load offset=12
    local.get 4
    i32.load offset=28
    i32.store
    local.get 4
    i32.load offset=12
    local.get 4
    i32.load offset=24
    i32.store offset=4
    local.get 4
    i32.load offset=12
    local.get 4
    i32.load offset=20
    i32.store offset=8
    local.get 4
    i32.load offset=12
    local.get 4
    i32.load offset=16
    i32.store offset=12
    local.get 4
    i32.load offset=12
    local.set 0
    local.get 4
    i32.const 32
    i32.add
    global.set 0
    local.get 0)
  (func $PInfo2Graph (type 0) (param i32) (result i32)
    (local i32 i32)
    global.get 0
    i32.const 48
    i32.sub
    local.tee 1
    global.set 0
    local.get 1
    local.get 0
    i32.store offset=44
    local.get 1
    local.get 1
    i32.load offset=44
    i32.load
    i32.store offset=40
    local.get 1
    local.get 1
    i32.load offset=44
    i32.load offset=4
    i32.store offset=36
    local.get 1
    local.get 1
    i32.load offset=44
    i32.load offset=8
    i32.store offset=32
    local.get 1
    local.get 1
    i32.load offset=44
    i32.load offset=12
    i32.store offset=28
    local.get 1
    local.get 1
    i32.load offset=40
    i32.const 1
    i32.add
    i32.const 2
    i32.shl
    call $malloc
    i32.store offset=24
    local.get 1
    i32.const 1
    i32.store offset=20
    block  ;; label = @1
      loop  ;; label = @2
        local.get 1
        i32.load offset=20
        local.get 1
        i32.load offset=40
        i32.le_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 1
        local.get 1
        i32.load offset=32
        local.get 1
        i32.load offset=20
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.store offset=16
        local.get 1
        i32.load offset=20
        local.set 0
        local.get 1
        i32.load offset=16
        local.set 2
        call $emptyLst
        drop
        local.get 1
        local.get 0
        local.get 2
        i32.const 0
        call $createNode
        i32.store offset=12
        local.get 1
        i32.load offset=24
        local.get 1
        i32.load offset=20
        i32.const 2
        i32.shl
        i32.add
        local.get 1
        i32.load offset=12
        i32.store
        local.get 1
        local.get 1
        i32.load offset=20
        i32.const 1
        i32.add
        i32.store offset=20
        br 0 (;@2;)
      end
    end
    local.get 1
    i32.const 0
    i32.store offset=8
    block  ;; label = @1
      loop  ;; label = @2
        local.get 1
        i32.load offset=8
        local.get 1
        i32.load offset=36
        i32.const 1
        i32.shl
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 1
        local.get 1
        i32.load offset=28
        local.get 1
        i32.load offset=8
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.store offset=4
        local.get 1
        local.get 1
        i32.load offset=28
        local.get 1
        i32.load offset=8
        i32.const 1
        i32.add
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.store
        local.get 1
        i32.load offset=24
        local.get 1
        i32.load offset=4
        i32.const 2
        i32.shl
        i32.add
        i32.load
        local.get 1
        i32.load
        call $addNghbr
        local.get 1
        local.get 1
        i32.load offset=8
        i32.const 2
        i32.add
        i32.store offset=8
        br 0 (;@2;)
      end
    end
    local.get 1
    i32.load offset=40
    local.get 1
    i32.load offset=36
    local.get 1
    i32.load offset=24
    call $createGraph
    local.set 0
    local.get 1
    i32.const 48
    i32.add
    global.set 0
    local.get 0)
  (func $parseInput (type 2) (result i32)
    (local i32 i32)
    global.get 0
    i32.const 48
    i32.sub
    local.tee 0
    global.set 0
    local.get 0
    i32.const 1024
    i32.symbolic
    i32.store offset=44
    local.get 0
    i32.const 1026
    i32.symbolic
    i32.store offset=40
    local.get 0
    local.get 0
    i32.load offset=44
    i32.const 1
    i32.add
    i32.const 2
    i32.shl
    call $malloc
    i32.store offset=36
    local.get 0
    i32.const 0
    i32.store offset=32
    block  ;; label = @1
      loop  ;; label = @2
        local.get 0
        i32.load offset=32
        local.get 0
        i32.load offset=44
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 0
        i32.const 1030
        i32.symbolic
        i32.store offset=28
        local.get 0
        i32.load offset=36
        local.get 0
        i32.load offset=32
        i32.const 1
        i32.add
        i32.const 2
        i32.shl
        i32.add
        local.get 0
        i32.load offset=28
        i32.store
        local.get 0
        local.get 0
        i32.load offset=32
        i32.const 1
        i32.add
        i32.store offset=32
        br 0 (;@2;)
      end
    end
    local.get 0
    local.get 0
    i32.load offset=40
    i32.const 2
    i32.shl
    i32.const 1
    i32.shl
    call $malloc
    i32.store offset=24
    local.get 0
    i32.const 0
    i32.store offset=20
    block  ;; label = @1
      loop  ;; label = @2
        local.get 0
        i32.load offset=20
        local.get 0
        i32.load offset=40
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 0
        i32.const 1030
        i32.symbolic
        i32.store offset=16
        local.get 0
        i32.const 1028
        i32.symbolic
        i32.store offset=12
        local.get 0
        i32.load offset=24
        local.get 0
        i32.load offset=20
        i32.const 1
        i32.shl
        i32.const 2
        i32.shl
        i32.add
        local.get 0
        i32.load offset=16
        i32.store
        local.get 0
        i32.load offset=24
        local.get 0
        i32.load offset=20
        i32.const 1
        i32.shl
        i32.const 1
        i32.add
        i32.const 2
        i32.shl
        i32.add
        local.get 0
        i32.load offset=12
        i32.store
        local.get 0
        local.get 0
        i32.load offset=20
        i32.const 1
        i32.add
        i32.store offset=20
        br 0 (;@2;)
      end
    end
    local.get 0
    i32.load offset=44
    local.get 0
    i32.load offset=40
    local.get 0
    i32.load offset=36
    local.get 0
    i32.load offset=24
    call $createPInfo
    local.set 1
    local.get 0
    i32.const 48
    i32.add
    global.set 0
    local.get 1)
  (func $reverseArray (type 1) (param i32 i32) (result i32)
    (local i32)
    global.get 0
    i32.const 32
    i32.sub
    local.tee 2
    global.set 0
    local.get 2
    local.get 0
    i32.store offset=28
    local.get 2
    local.get 1
    i32.store offset=24
    local.get 2
    local.get 2
    i32.load offset=24
    i32.const 2
    i32.shl
    call $malloc
    i32.store offset=20
    local.get 2
    local.get 2
    i32.load offset=24
    i32.const 1
    i32.sub
    i32.store offset=16
    local.get 2
    i32.const 0
    i32.store offset=12
    block  ;; label = @1
      loop  ;; label = @2
        local.get 2
        i32.load offset=12
        local.get 2
        i32.load offset=24
        i32.lt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 2
        i32.load offset=20
        local.get 2
        i32.load offset=12
        i32.const 2
        i32.shl
        i32.add
        local.get 2
        i32.load offset=28
        local.get 2
        i32.load offset=16
        local.get 2
        i32.load offset=12
        i32.sub
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.store
        local.get 2
        local.get 2
        i32.load offset=12
        i32.const 1
        i32.add
        i32.store offset=12
        br 0 (;@2;)
      end
    end
    local.get 2
    i32.load offset=20
    local.set 0
    local.get 2
    i32.const 32
    i32.add
    global.set 0
    local.get 0)
  (func $sccs (type 0) (param i32) (result i32)
    (local i32)
    global.get 0
    i32.const 32
    i32.sub
    local.tee 1
    global.set 0
    local.get 1
    local.get 0
    i32.store offset=28
    local.get 1
    local.get 1
    i32.load offset=28
    i32.const 0
    call $dfs
    i32.store offset=24
    local.get 1
    local.get 1
    i32.load offset=28
    call $graphTranspose
    i32.store offset=20
    local.get 1
    local.get 1
    i32.load offset=24
    i32.load offset=24
    local.get 1
    i32.load offset=28
    i32.load
    call $reverseArray
    i32.store offset=16
    local.get 1
    local.get 1
    i32.load offset=20
    local.get 1
    i32.load offset=16
    call $dfs
    i32.store offset=12
    local.get 1
    i32.load offset=12
    local.set 0
    local.get 1
    i32.const 32
    i32.add
    global.set 0
    local.get 0)
  (func $createSCCGraph (type 3) (param i32 i32 i32) (result i32)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 3
    global.set 0
    local.get 3
    local.get 0
    i32.store offset=12
    local.get 3
    local.get 1
    i32.store offset=8
    local.get 3
    local.get 2
    i32.store offset=4
    local.get 3
    i32.const 12
    call $malloc
    i32.store
    local.get 3
    i32.load
    local.get 3
    i32.load offset=12
    i32.store offset=4
    local.get 3
    i32.load
    local.get 3
    i32.load offset=8
    i32.store
    local.get 3
    i32.load
    local.get 3
    i32.load offset=4
    i32.store offset=8
    local.get 3
    i32.load
    local.set 0
    local.get 3
    i32.const 16
    i32.add
    global.set 0
    local.get 0)
  (func $findMaxPriceAndSetMapping (type 5) (param i32 i32 i32 i32) (result i32)
    (local i32)
    global.get 0
    i32.const 32
    i32.sub
    local.tee 4
    local.get 0
    i32.store offset=28
    local.get 4
    local.get 1
    i32.store offset=24
    local.get 4
    local.get 2
    i32.store offset=20
    local.get 4
    local.get 3
    i32.store offset=16
    local.get 4
    i32.const -1
    i32.store offset=12
    local.get 4
    local.get 4
    i32.load offset=28
    i32.load offset=8
    i32.store offset=8
    block  ;; label = @1
      loop  ;; label = @2
        local.get 4
        i32.load offset=24
        i32.const 0
        i32.ne
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 4
        local.get 4
        i32.load offset=24
        i32.load
        i32.store offset=4
        local.get 4
        local.get 4
        i32.load offset=8
        local.get 4
        i32.load offset=4
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.load offset=4
        i32.store
        block  ;; label = @3
          block  ;; label = @4
            local.get 4
            i32.load offset=12
            local.get 4
            i32.load
            i32.lt_s
            i32.const 1
            i32.and
            i32.eqz
            br_if 0 (;@4;)
            local.get 4
            i32.load
            local.set 0
            br 1 (;@3;)
          end
          local.get 4
          i32.load offset=12
          local.set 0
        end
        local.get 4
        local.get 0
        i32.store offset=12
        local.get 4
        i32.load offset=20
        local.get 4
        i32.load offset=4
        i32.const 2
        i32.shl
        i32.add
        local.get 4
        i32.load offset=16
        i32.store
        local.get 4
        local.get 4
        i32.load offset=24
        i32.load offset=8
        i32.store offset=24
        br 0 (;@2;)
      end
    end
    local.get 4
    i32.load offset=12)
  (func $DFSInfo2SCCGraph (type 1) (param i32 i32) (result i32)
    (local i32)
    global.get 0
    i32.const 96
    i32.sub
    local.tee 2
    global.set 0
    local.get 2
    local.get 0
    i32.store offset=92
    local.get 2
    local.get 1
    i32.store offset=88
    local.get 2
    local.get 2
    i32.load offset=92
    i32.load offset=28
    i32.store offset=84
    local.get 2
    local.get 2
    i32.load offset=92
    i32.load offset=32
    i32.store offset=80
    local.get 2
    i32.const 0
    i32.store offset=76
    local.get 2
    local.get 2
    i32.load offset=88
    i32.load
    i32.store offset=72
    local.get 2
    local.get 2
    i32.load offset=72
    i32.const 1
    i32.add
    i32.const 2
    i32.shl
    call $malloc
    i32.store offset=68
    local.get 2
    local.get 2
    i32.load offset=80
    i32.const 2
    i32.add
    i32.const 2
    i32.shl
    call $malloc
    i32.store offset=64
    local.get 2
    i32.const 0
    i32.store offset=60
    block  ;; label = @1
      loop  ;; label = @2
        local.get 2
        i32.load offset=60
        local.get 2
        i32.load offset=80
        i32.le_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 2
        local.get 2
        i32.load offset=84
        local.get 2
        i32.load offset=60
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.store offset=56
        local.get 2
        local.get 2
        i32.load offset=88
        local.get 2
        i32.load offset=56
        local.get 2
        i32.load offset=68
        local.get 2
        i32.load offset=60
        i32.const 1
        i32.add
        call $findMaxPriceAndSetMapping
        i32.store offset=52
        local.get 2
        i32.load offset=60
        local.set 0
        local.get 2
        i32.load offset=52
        local.set 1
        call $emptyLst
        drop
        local.get 2
        local.get 0
        i32.const 1
        i32.add
        local.get 1
        i32.const 0
        call $createNode
        i32.store offset=48
        local.get 2
        i32.load offset=64
        local.get 2
        i32.load offset=60
        i32.const 1
        i32.add
        i32.const 2
        i32.shl
        i32.add
        local.get 2
        i32.load offset=48
        i32.store
        local.get 2
        local.get 2
        i32.load offset=60
        i32.const 1
        i32.add
        i32.store offset=60
        br 0 (;@2;)
      end
    end
    local.get 2
    i32.const 1
    i32.store offset=44
    block  ;; label = @1
      loop  ;; label = @2
        local.get 2
        i32.load offset=44
        local.get 2
        i32.load offset=72
        i32.le_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 2
        local.get 2
        i32.load offset=88
        i32.load offset=8
        local.get 2
        i32.load offset=44
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.store offset=40
        local.get 2
        local.get 2
        i32.load offset=68
        local.get 2
        i32.load offset=40
        i32.load
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.store offset=36
        local.get 2
        local.get 2
        i32.load offset=40
        i32.load offset=8
        i32.store offset=32
        block  ;; label = @3
          loop  ;; label = @4
            local.get 2
            i32.load offset=32
            i32.const 0
            i32.ne
            i32.const 1
            i32.and
            i32.eqz
            br_if 1 (;@3;)
            local.get 2
            local.get 2
            i32.load offset=32
            i32.load
            i32.store offset=28
            local.get 2
            local.get 2
            i32.load offset=68
            local.get 2
            i32.load offset=28
            i32.const 2
            i32.shl
            i32.add
            i32.load
            i32.store offset=24
            block  ;; label = @5
              local.get 2
              i32.load offset=36
              local.get 2
              i32.load offset=24
              i32.ne
              i32.const 1
              i32.and
              i32.eqz
              br_if 0 (;@5;)
              local.get 2
              local.get 2
              i32.load offset=64
              local.get 2
              i32.load offset=36
              i32.const 2
              i32.shl
              i32.add
              i32.load
              i32.store offset=20
              local.get 2
              i32.load offset=20
              local.get 2
              i32.load offset=24
              call $addNghbr
              local.get 2
              local.get 2
              i32.load offset=76
              i32.const 1
              i32.add
              i32.store offset=76
            end
            local.get 2
            local.get 2
            i32.load offset=32
            i32.load offset=8
            i32.store offset=32
            br 0 (;@4;)
          end
        end
        local.get 2
        local.get 2
        i32.load offset=44
        i32.const 1
        i32.add
        i32.store offset=44
        br 0 (;@2;)
      end
    end
    local.get 2
    local.get 2
    i32.load offset=80
    local.get 2
    i32.load offset=76
    local.get 2
    i32.load offset=64
    call $createGraph
    i32.store offset=16
    local.get 2
    local.get 2
    i32.load offset=16
    local.get 2
    i32.load offset=72
    local.get 2
    i32.load offset=68
    call $createSCCGraph
    i32.store offset=12
    local.get 2
    i32.load offset=12
    local.set 0
    local.get 2
    i32.const 96
    i32.add
    global.set 0
    local.get 0)
  (func $recomputePrices (type 6) (param i32)
    (local i32)
    global.get 0
    i32.const 32
    i32.sub
    local.tee 1
    local.get 0
    i32.store offset=28
    local.get 1
    local.get 1
    i32.load offset=28
    i32.load
    i32.store offset=24
    local.get 1
    local.get 1
    i32.load offset=28
    i32.load offset=8
    i32.store offset=20
    local.get 1
    local.get 1
    i32.load offset=24
    i32.store offset=16
    block  ;; label = @1
      loop  ;; label = @2
        local.get 1
        i32.load offset=16
        i32.const 0
        i32.gt_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 1
        local.get 1
        i32.load offset=20
        local.get 1
        i32.load offset=16
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.store offset=12
        local.get 1
        local.get 1
        i32.load offset=12
        i32.load offset=8
        i32.store offset=8
        local.get 1
        local.get 1
        i32.load offset=12
        i32.load offset=4
        i32.store offset=4
        block  ;; label = @3
          loop  ;; label = @4
            local.get 1
            i32.load offset=8
            i32.const 0
            i32.ne
            i32.const 1
            i32.and
            i32.eqz
            br_if 1 (;@3;)
            local.get 1
            local.get 1
            i32.load offset=20
            local.get 1
            i32.load offset=8
            i32.load
            i32.const 2
            i32.shl
            i32.add
            i32.load
            i32.load offset=4
            i32.store
            block  ;; label = @5
              block  ;; label = @6
                local.get 1
                i32.load
                local.get 1
                i32.load offset=4
                i32.gt_s
                i32.const 1
                i32.and
                i32.eqz
                br_if 0 (;@6;)
                local.get 1
                i32.load
                local.set 0
                br 1 (;@5;)
              end
              local.get 1
              i32.load offset=4
              local.set 0
            end
            local.get 1
            local.get 0
            i32.store offset=4
            local.get 1
            local.get 1
            i32.load offset=8
            i32.load offset=8
            i32.store offset=8
            br 0 (;@4;)
          end
        end
        local.get 1
        i32.load offset=12
        local.get 1
        i32.load offset=4
        i32.store offset=4
        local.get 1
        local.get 1
        i32.load offset=16
        i32.const -1
        i32.add
        i32.store offset=16
        br 0 (;@2;)
      end
    end)
  (func $printNewPrices (type 6) (param i32)
    (local i32)
    global.get 0
    i32.const 32
    i32.sub
    local.tee 1
    global.set 0
    local.get 1
    local.get 0
    i32.store offset=28
    local.get 1
    local.get 1
    i32.load offset=28
    i32.load
    i32.store offset=24
    local.get 1
    local.get 1
    i32.load offset=28
    i32.load offset=8
    i32.store offset=20
    local.get 1
    local.get 1
    i32.load offset=28
    i32.load offset=4
    i32.store offset=16
    local.get 1
    local.get 1
    i32.load offset=16
    i32.load offset=8
    i32.store offset=12
    local.get 1
    i32.const 1
    i32.store offset=8
    block  ;; label = @1
      loop  ;; label = @2
        local.get 1
        i32.load offset=8
        local.get 1
        i32.load offset=24
        i32.le_s
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
        local.get 1
        local.get 1
        i32.load offset=12
        local.get 1
        i32.load offset=20
        local.get 1
        i32.load offset=8
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.const 2
        i32.shl
        i32.add
        i32.load
        i32.load offset=4
        i32.store offset=4
        local.get 1
        local.get 1
        i32.load offset=4
        i32.store
        i32.const 1032
        local.get 1
        call $printf
        drop
        local.get 1
        local.get 1
        i32.load offset=8
        i32.const 1
        i32.add
        i32.store offset=8
        br 0 (;@2;)
      end
    end
    local.get 1
    i32.const 32
    i32.add
    global.set 0)
  (func $__original_main (type 2) (result i32)
    (local i32)
    global.get 0
    i32.const 32
    i32.sub
    local.tee 0
    global.set 0
    local.get 0
    call $parseInput
    i32.store offset=28
    local.get 0
    local.get 0
    i32.load offset=28
    call $PInfo2Graph
    i32.store offset=24
    local.get 0
    local.get 0
    i32.load offset=24
    i32.const 0
    call $dfs
    i32.store offset=20
    local.get 0
    local.get 0
    i32.load offset=24
    call $sccs
    i32.store offset=16
    local.get 0
    local.get 0
    i32.load offset=16
    local.get 0
    i32.load offset=24
    call $DFSInfo2SCCGraph
    i32.store offset=12
    local.get 0
    i32.load offset=12
    i32.load offset=4
    call $recomputePrices
    local.get 0
    i32.load offset=12
    call $printNewPrices
    local.get 0
    i32.const 32
    i32.add
    global.set 0
    i32.const 0)
  (func $printf (type 1) (param i32 i32) (result i32)
    (local i32 i32 i32 i32)
    global.get 0
    local.set 2
    i32.const 16
    local.set 3
    local.get 2
    local.get 3
    i32.sub
    local.set 4
    local.get 4
    local.get 0
    i32.store offset=12
    i32.const 0
    local.set 5
    local.get 5
    return)
  (func $malloc (type 0) (param i32) (result i32)
    (local i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32)
    global.get 0
    local.set 1
    i32.const 16
    local.set 2
    local.get 1
    local.get 2
    i32.sub
    local.set 3
    local.get 3
    global.set 0
    local.get 3
    local.get 0
    i32.store offset=12
    i32.const 0
    local.set 4
    local.get 4
    i32.load offset=1068
    local.set 5
    local.get 3
    local.get 5
    i32.store offset=8
    local.get 3
    i32.load offset=12
    local.set 6
    i32.const 0
    local.set 7
    local.get 7
    i32.load offset=1068
    local.set 8
    local.get 8
    local.get 6
    i32.add
    local.set 9
    i32.const 0
    local.set 10
    local.get 10
    local.get 9
    i32.store offset=1068
    local.get 3
    i32.load offset=8
    local.set 11
    local.get 3
    i32.load offset=12
    local.set 12
    local.get 11
    local.get 12
    alloc
    local.set 13
    i32.const 16
    local.set 14
    local.get 3
    local.get 14
    i32.add
    local.set 15
    local.get 15
    global.set 0
    local.get 13
    return)
  (func $calloc (type 1) (param i32 i32) (result i32)
    (local i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32)
    global.get 0
    local.set 2
    i32.const 16
    local.set 3
    local.get 2
    local.get 3
    i32.sub
    local.set 4
    local.get 4
    global.set 0
    local.get 4
    local.get 0
    i32.store offset=12
    local.get 4
    local.get 1
    i32.store offset=8
    i32.const 0
    local.set 5
    local.get 5
    i32.load offset=1068
    local.set 6
    local.get 4
    local.get 6
    i32.store offset=4
    local.get 4
    i32.load offset=12
    local.set 7
    local.get 4
    i32.load offset=8
    local.set 8
    local.get 7
    local.get 8
    i32.mul
    local.set 9
    i32.const 0
    local.set 10
    local.get 10
    i32.load offset=1068
    local.set 11
    local.get 11
    local.get 9
    i32.add
    local.set 12
    i32.const 0
    local.set 13
    local.get 13
    local.get 12
    i32.store offset=1068
    local.get 4
    i32.load offset=4
    local.set 14
    local.get 4
    i32.load offset=12
    local.set 15
    local.get 4
    i32.load offset=8
    local.set 16
    local.get 15
    local.get 16
    i32.mul
    local.set 17
    local.get 14
    local.get 17
    alloc
    local.set 18
    i32.const 16
    local.set 19
    local.get 4
    local.get 19
    i32.add
    local.set 20
    local.get 20
    global.set 0
    local.get 18
    return)
  (func $__WASP_alloc (type 1) (param i32 i32) (result i32)
    (local i32 i32 i32 i32)
    global.get 0
    local.set 2
    i32.const 16
    local.set 3
    local.get 2
    local.get 3
    i32.sub
    local.set 4
    local.get 4
    local.get 0
    i32.store offset=12
    local.get 4
    local.get 1
    i32.store offset=8
    local.get 4
    i32.load offset=12
    local.set 5
    local.get 5
    return)
  (func $__WASP_symb_int (type 0) (param i32) (result i32)
    (local i32 i32 i32 i32)
    global.get 0
    local.set 1
    i32.const 16
    local.set 2
    local.get 1
    local.get 2
    i32.sub
    local.set 3
    local.get 3
    local.get 0
    i32.store offset=12
    i32.const 0
    local.set 4
    local.get 4
    return)
  (table (;0;) 1 1 funcref)
  (memory (;0;) 2)
  (global (;0;) (mut i32) (i32.const 66608))
  (export "memory" (memory 0))
  (export "__original_main" (func $__original_main))
  (data (;0;) (i32.const 1024) "n\00m\00k\00j\00%d\0a\00visit invoked on visted node!\0a\00")
  (data (;1;) (i32.const 1068) "0\04\01\00"))
