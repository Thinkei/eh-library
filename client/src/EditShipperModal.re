open Ehd;
open Shipper;

let s = ReasonReact.string;

[@react.component]
let make =
    (
      ~openModal,
      ~toggleEditModal,
      ~editingShipper,
      ~resetEditingShipper,
      ~updateShipper,
    ) => {
  let (name, setName) = React.useState(() => editingShipper.name);
  let (info, setInfo) = React.useState(() => editingShipper.info);

  <Modal
    visible=openModal
    onCancel={_ => {
      toggleEditModal(false);
      resetEditingShipper();
    }}
    onOk={_ => {
      updateShipper({id: editingShipper.id, name, info});
      resetEditingShipper();
    }}>
    <div style={ReactDOMRe.Style.make(~display="grid", ())}>
      <Input
        defaultValue=name
        onChange={e => setName(e->ReactEvent.Form.target##value)}
      />
      <Input.TextArea
        defaultValue=info
        onChange={e => setInfo(e->ReactEvent.Form.target##value)}
      />
    </div>
  </Modal>;
};
