import Foundation

struct PokemonListResults: Codable { //stores the list of 151 pokemon
    let results: [PokemonListResult]
}

struct PokemonListResult: Codable { //stores the name of pokemon and its url
    let name: String
    let url: String
}

struct PokemonResult: Codable {
    let id: Int //id of pokemon
    let name: String //name of pokemon
    let types: [PokemonTypeEntry] //stores a list of types each pokemon has
}

struct PokemonTypeEntry: Codable {
    let slot: Int //slot that corresponds to position/number of pokemon type
    let type: PokemonType //stores type of pokemon
}

struct PokemonType: Codable { //type of pokemon
    let name: String
}

struct PokemonSprites: Codable {
    let id: Int //id of pokemon
    let name: String //name of pokemon
    let sprites: PokemonSprite
}

struct PokemonSprite: Codable {
    let front_default: String //url to sprite image.png
}

struct PokemonSpecies: Codable {
    let id: Int //id of pokemon
    let name: String //name of pokemon
    let species: PokemonSpeciesUrl //stores a list of types each pokemon has
}

struct PokemonSpeciesUrl: Codable {
    //let id: Int //identifier for this resource
    let name: String //name of pokemon
    let url: String //url to pokemon species
    //let flavour_text_entries: [PokemonDescription] //problem
    //let url: String //go to this url to find more info on pokemon-species
}

struct PokemonFlavourEntries: Codable {
    let id: Int //id of pokemon
    let name: String //name of pokemon
    let flavor_text_entries: [PokemonDescription] //54 array of flavour text //add the first eng descr
}

struct PokemonDescription: Codable { //in pokemon-species
    let flavor_text: String
    let language: PokemonLanguage
}

struct PokemonLanguage: Codable {
    let name: String //e.g. ja/en
    //let url: String
}

struct PokemonCaught {
    var caught = [String: Bool]() //create dictionary. caught is of type dictionary
}


/*struct catchPokemon: Codable {
    let name: String
    var caught: Bool
}*/
