let to_s = ReasonReact.string;

module FormStyle = {
  open Css;

  let form = [
    20 |> px |> paddingLeft,
    flexBox |> display
  ] |> style;

  let item = [
    10 |> px |> marginLeft
  ] |> style;

  let button = [
    10 |> px |> marginLeft,
    `pointer |> cursor,
    "fff" |> hex |> color,
    "007bff" |> hex |> backgroundColor,
    "007bff" |> hex |> borderColor,
    0.75 |> rem |> borderRadius
  ] |> style;
};

module AddNewBookForm = {
  [@react.component]
  let make = () => {
    <div className=FormStyle.form>
      <div>
        <input
        value=""
        placeholder="Title"
        />
      </div>

      <div className=FormStyle.item>
        <input
        value=""
        placeholder="Tags"
        />
      </div>

      <button className=FormStyle.button>
        {ReasonReact.string("Add new book")}
      </button>
    </div>;
  }
}


/*module AddNewBookForm = {*/
  /*[@react.component]*/

  /*let make = () => {*/
    /*<div>*/
    /*</div>*/
  /*}*/
/*}*/
