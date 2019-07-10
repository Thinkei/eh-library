open Route;

[@react.component]
let make = () =>
  <>
    <Link route=Config.Books> {ReasonReact.string("Books")} </Link>
    <br />
    <Link route=Config.MyProfile> {ReasonReact.string("My Profile")} </Link>
    <br/>
    <Link route=Config.Shipper> {ReasonReact.string("Shipper")} </Link>
  </>;
