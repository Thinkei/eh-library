type shipper = {
  id: int,
  name: string,
  info: string,
};

let s = ReasonReact.string;

module Styles = {
  open Css;

  let wrapper =
    [
      display(grid),
      gridGap(em(1.0)),
      gridTemplateColumns([px(350), fr(1.0)]),
    ]
    |> style;

  let form = [display(`flex), flexDirection(column)] |> style;

  let table = [border(px(1), solid, grey)] |> style;

  let button =
    [
      color(white),
      borderRadius(px(5)),
      background(hex("3498db")),
      borderColor(hex("f2f2f2")),
      padding2(~v=em(1.0), ~h=em(2.5)),
    ]
    |> style;

  let fieldBase = [
    flexGrow(1.0),
    borderRadius(px(5)),
    marginBottom(px(10)),
    border(px(1), solid, hex("bdc3c7")),
    padding2(~v=em(1.0), ~h=em(0.5)),
  ];

  let fieldTextarea = [height(px(150))];

  let field = style(fieldBase);

  let textarea = [fieldBase, fieldTextarea] |> List.concat |> style;
};

module ShipperRow = {
  [@react.component]
  let make = (~id, ~name, ~info, ~setShipperToEdit) =>
    <tr>
      <td> {string_of_int(id) |> s} </td>
      <td> {name |> s} </td>
      <td> {info |> s} </td>
      <td>
        <button
          className=Styles.button
          onClick={_ => setShipperToEdit({id, name, info})}>
          {s("Edit")}
        </button>
      </td>
    </tr>;
};

let initialShippers = [{id: 0, name: "Xtay Pro", info: "xtaypro.com"}];

module NewShipperForm = {
  [@react.component]
  let make = (~shippers, ~addShipper) => {
    let (name, setName) = React.useState(() => "");
    let (info, setInfo) = React.useState(() => "");
    <div className=Styles.form>
      <h4> {s("Create Shipper")} </h4>
      <input
        className=Styles.field
        value=name
        type_="text"
        placeholder="Shipper's Name"
        onChange={e => setName(e->ReactEvent.Form.target##value)}
      />
      <textarea
        className=Styles.textarea
        value=info
        type_="text"
        placeholder="Shipper's Info"
        onChange={e => setInfo(e->ReactEvent.Form.target##value)}
      />
      <button
        className=Styles.button
        type_="submit"
        onClick={_ => addShipper({id: List.length(shippers), name, info})}>
        {s("Add")}
      </button>
    </div>;
  };
};

module EditShipperForm = {
  [@react.component]
  let make = (~shipperEdit, ~saveEditingShipper, ~updateEditingShipper) => {
    let handleSave = () => {
      saveEditingShipper({
        id: shipperEdit.id,
        name: shipperEdit.name,
        info: shipperEdit.info,
      });
      updateEditingShipper({id: (-1), name: "", info: ""});
    };

    <div className=Styles.form>
      <h4> {s("Edit Shipper")} </h4>
      <input
        className=Styles.field
        value={shipperEdit.name}
        type_="text"
        placeholder="Shipper's Name"
        onChange={e =>
          updateEditingShipper({
            id: shipperEdit.id,
            info: shipperEdit.info,
            name: e->ReactEvent.Form.target##value,
          })
        }
      />
      <textarea
        className=Styles.textarea
        value={shipperEdit.info}
        type_="text"
        placeholder="Shipper's Info"
        onChange={e =>
          updateEditingShipper({
            id: shipperEdit.id,
            name: shipperEdit.name,
            info: e->ReactEvent.Form.target##value,
          })
        }
      />
      <button
        className=Styles.button type_="submit" onClick={_ => handleSave()}>
        {s("Save")}
      </button>
    </div>;
  };
};

[@react.component]
let make = () => {
  let (shippers, setShippers) = React.useState(() => initialShippers);
  let (shipperEdit, setShipperEdit) =
    React.useState(() => {id: (-1), name: "", info: ""});

  let handleEdit = updateInfo =>
    setShippers(_ =>
      List.map(
        shipper =>
          if (shipper.id === shipperEdit.id) {
            {id: shipper.id, name: updateInfo.name, info: updateInfo.info};
          } else {
            shipper;
          },
        shippers,
      )
    );
  <div className=Styles.wrapper>
    <NewShipperForm
      shippers
      addShipper={shipper => setShippers(bs => [shipper, ...bs])}
    />
    <table className=Styles.table>
      <tr>
        <td> {s("ID")} </td>
        <td> {s("Name")} </td>
        <td> {s("Info")} </td>
        <td> {s("Actions")} </td>
      </tr>
      {shippers
       |> List.map(shipper =>
            <ShipperRow
              id={shipper.id}
              name={shipper.name}
              info={shipper.info}
              setShipperToEdit={sh => setShipperEdit(_ => sh)}
            />
          )
       |> Array.of_list
       |> ReasonReact.array}
    </table>
    <EditShipperForm
      saveEditingShipper={updateInfo => handleEdit(updateInfo)}
      shipperEdit
      updateEditingShipper={sh => setShipperEdit(_ => sh)}
    />
  </div>;
};
