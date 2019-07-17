type shipper = {
  name: string,
  info: string,
};

let s = ReasonReact.string;

module Styles = {
  open Css;

  let wrapper = [
    display(grid),
    gridGap(em(1.0)),
    gridTemplateColumns([px(350), fr(1.0)])
  ] |> style;

  let form = [
    display(`flex),
    flexDirection(column)
  ] |> style;

  let table = [
    border(px(1), solid, grey)
  ] |> style;

  let button = [
    color(white),
    borderRadius(px(5)),
    background(hex("3498db")),
    borderColor(hex("f2f2f2")),
    padding2(~v=em(1.0), ~h=em(2.5)),
  ] |> style

  let fieldBase = [
    flexGrow(1.0),
    borderRadius(px(5)),
    marginBottom(px(10)),
    border(px(1), solid, hex("bdc3c7")),
    padding2(~v=em(1.0), ~h=em(0.5)),
  ];

  let fieldTextarea = [
    height(px(150))
  ];

  let field = style(fieldBase);

  let textarea = [fieldBase, fieldTextarea] |> List.concat |> style;
};

module ShipperRow = {
  [@react.component]
  let make = (~name, ~info) => <tr>
    <td> {name |> s} </td>
    <td> {info |> s} </td>
    </tr>;
};

let initialShippers = [{name: "Xtay Pro", info: "xtaypro.com"}];

module NewShipperForm = {
  [@react.component]
  let make = (~addShipper) => {
    let (name, setName) = React.useState(() => "");
    let (info, setInfo) = React.useState(() => "");
    <div className=Styles.form>
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
        onClick={_ => addShipper({ name, info })}>
        {s("Add")}
      </button>
    </div>;
  };
};

[@react.component]
let make = () => {
  let (shippers, setShippers) = React.useState(() => initialShippers);

  <div className=Styles.wrapper>
    <NewShipperForm addShipper={shipper => setShippers(bs => [shipper, ...bs])} />
    <table className=Styles.table>
      <tr>
        <td>{s("Name")}</td>
        <td>{s("Info")}</td>
      </tr>
      {shippers
        |> List.map(shipper => <ShipperRow name={shipper.name} info={shipper.info} />)
        |> Array.of_list
        |> ReasonReact.array}
    </table>
  </div>;
};
